using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine.UI;

namespace Net
{
    public enum HEAD
    {
        NULL = 0,
        FINDPLAYER,
        JANKEN,
        JANKEN_RESULT,
        SET,
        OTHER_SET,
        SURRENDER,
        OTHER_SURRENDER,
        WIN,
        DISCONNECT,
        OTHER_DISCONNECT,
        RESTART,
        OTHER_RESTART,
        PLAYERNAME,
        OTHER_PLAYERNAME,
        INVALID,
        ACK
    }
    public enum DATA
    {
        JANKEN_LOSE = 0,
        JANKEN_WIN,
        JANKEN_DRAW,
        JANKEN_ROCK,
        JANKEN_PAPER,
        JANKEN_SCISSORS
    }
    public class Client
    {
        public const int MSG_LENTH = 16;
        private static byte[] msg = new byte[MSG_LENTH];
        private static byte[] msg_r = new byte[MSG_LENTH];
        private static Socket socket;
        private static bool inited;
        private static bool is_connected;
        public static void start()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            Menu = GameObject.Find("Menu");
            nickname = Menu.transform.Find("nickname").gameObject.GetComponent<InputField>();
            message = Menu.transform.Find("Message").gameObject.GetComponent<Text>();
            selfname = Menu.transform.Find("selfname").gameObject.GetComponent<Text>();
            othername = Menu.transform.Find("othername").gameObject.GetComponent<Text>();
            pause = Menu.transform.Find("pause").gameObject.GetComponent<Button>();
            janken_rock = Menu.transform.Find("janken_rock").gameObject.GetComponent<Button>();
            janken_scissors = Menu.transform.Find("janken_scissors").gameObject.GetComponent<Button>();
            janken_paper = Menu.transform.Find("janken_paper").gameObject.GetComponent<Button>();
            //...ing
            inited = true;
        }
        public static bool is_inited()
        {
            return inited;
        }
        public static bool connect(string ip, int port)
        {
            IPAddress mIp = IPAddress.Parse(ip);
            IPEndPoint ip_end_point = new IPEndPoint(mIp, port);
            try
            {
                socket.Connect(ip_end_point);
                is_connected = true;
                Debug.Log("连接服务器成功");
                return is_connected;
            }
            catch
            {
                is_connected = false;
                Debug.Log("连接服务器失败");
                return is_connected;
            }
        }
        public static void set_msg(byte head,byte[] data)
        {
            msg[0] = head;
            data.CopyTo(msg, 1);
        }
        public static void send()
        {
            if (is_connected == false) return;
            try
            {
                socket.Send(msg);
            }catch
            {
                is_connected = false;
                socket.Shutdown(SocketShutdown.Both);
                socket.Close();
            }
        }
        public static void receive()
        {
            if (is_connected == false) return;
            socket.BeginReceive(msg_r, 0, msg_r.Length, 0, new System.AsyncCallback(receive_handler), socket);
        }
        private static void receive_handler(System.IAsyncResult ar)
        {
            HEAD head = (HEAD)msg_r[0];
            byte[] data = new byte[MSG_LENTH - 1];
            System.Array.Copy(msg_r, 1, data, 0, MSG_LENTH - 1);

            switch (head)
            {
                case HEAD.FINDPLAYER:
                    handler_findplayer();
                    break;
                case HEAD.OTHER_PLAYERNAME:
                    handler_other_playname();
                    break;
                case HEAD.JANKEN_RESULT:
                    handler_janken_result();
                    break;
                case HEAD.OTHER_SET:
                    handler_other_set();
                    break;
                case HEAD.WIN:
                    handler_win();
                    break;
                default:

                    break;
            }

        }
        private static void handler_findplayer()
        {
            selfname.text = nickname.text;
            byte head = (byte)HEAD.PLAYERNAME;
            byte[] data = System.Text.Encoding.ASCII.GetBytes(selfname.text);
            set_msg(head, data);
            send();
            receive();
        }
        private static void handler_other_playname()
        {
            char[] name = new char[MSG_LENTH - 1];
            System.Array.Copy(msg_r, 1, name, 0, MSG_LENTH - 1);
            othername.text = name.ToString();

            selfname.gameObject.SetActive(true);
            othername.gameObject.SetActive(true);
            pause.gameObject.SetActive(true);
            janken_rock.gameObject.SetActive(true);
            janken_scissors.gameObject.SetActive(true);
            janken_paper.gameObject.SetActive(true);
        }
        private static void handler_janken_result()
        {
            DATA result = (DATA)msg_r[1];
            switch (result)
            {
                case DATA.JANKEN_DRAW:
                    janken_rock.gameObject.SetActive(true);
                    janken_scissors.gameObject.SetActive(true);
                    janken_paper.gameObject.SetActive(true);
                    break;
                case DATA.JANKEN_LOSE:
                    is_gaming = true;
                    chess_other = 1;
                    chess_self = 2;
                    receive();
                    break;
                case DATA.JANKEN_WIN:
                    is_gaming = true;
                    chess_self = 1;
                    chess_other = 2;
                    is_turn = true;
                    break;
                default:
                    break;
            }
        }
        private static void handler_other_set()
        {
            byte[] data = new byte[2];
            System.Array.Copy(msg_r, 1, data, 0, 2);
            int x = (int)data[0];
            int y = (int)data[1];
            chess_board[x, y] = chess_other;
            is_turn = true;
        }
        private static void handler_win()
        {
            byte data = msg_r[1];
            if (data == (byte)DATA.JANKEN_WIN)
            {
                message.text = "You win!";
                message.gameObject.SetActive(true);
                is_gaming = false;
            }else if (data == (byte)DATA.JANKEN_LOSE)
            {
                message.text = "You lose!";
                message.gameObject.SetActive(true);
                is_gaming = false;
            }else
            {
                message.text = "未知对局结果，请重开";
                message.gameObject.SetActive(true);
                is_gaming = false;
            }
        }
        /////////////////////////////////////////////////////////////////////////////////////////
        public static int chess_self;
        public static int chess_other;

        public static int[,] chess_board;

        public static bool is_turn;

        public static bool is_gaming;

        static GameObject Menu;

        static InputField nickname;
        static Text message;
        static Text selfname;
        static Text othername;
        static Button pause;
        static Button janken_rock;
        static Button janken_scissors;
        static Button janken_paper;
    }
}