using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.IO;
using UnityEngine.UI;
using System;

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
        ACK,
        TEST
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
            is_gaming = false;
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
                Debug.Log("Send seccussed");
            }catch
            {
                Debug.Log("Send failed");
                d_message = "连接出现异常";
                u_message = true;
                sa_message = true;
                is_connected = false;
                game_reset();
                close();
            }
        }
        public static void receive()
        {
            if (is_connected == false) return;
            socket.BeginReceive(msg_r, 0, msg_r.Length, 0, new System.AsyncCallback(receive_handler), socket);
        }
        private static void receive_handler(System.IAsyncResult ar)
        {
            Debug.Log("Receive a message : " + msg_r.ToString());
            HEAD head = (HEAD)msg_r[0];
            byte[] data = new byte[MSG_LENTH - 1];
            System.Array.Copy(msg_r, 1, data, 0, MSG_LENTH - 1);

            switch (head)
            {
                case HEAD.TEST:
                    byte[] tempmsg = new byte[MSG_LENTH + 1];
                    tempmsg[0] = 1;
                    tempmsg[MSG_LENTH] = 1;
                    try
                    {
                        socket.Send(tempmsg);
                    }
                    catch
                    {
                        d_message = "连接出现异常";
                        u_message = true;
                        sa_message = true;
                        is_connected = false;
                        game_reset();
                        close();
                        return;
                    }
                    receive();
                    break;
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
                case HEAD.OTHER_DISCONNECT:
                    handler_other_disconnect();
                    break;
                case HEAD.OTHER_SURRENDER:
                    handler_other_surrender();
                    break;
                case HEAD.OTHER_RESTART:
                    handler_other_restart();
                    break;
                case HEAD.INVALID:
                    handler_invalid();
                    break;
                default:
                    game_reset();
                    close();
                    break;
            }

        }

        private static void handler_invalid()
        {
            chess_board[last_x, last_y] = last_chess;
            is_turn = true;
            d_message = "下子位置错误，请重下";
            u_message = true;
            sa_message = true;
            se_waiting = true;
        }

        private static void handler_other_restart()
        {
            d_waiting = "对方请求重开";
            u_waiting = true;
            sa_waiting = true;

            sa_ACK = true;
            sa_disconnect = true;
        }

        private static void handler_other_surrender()
        {
            d_waiting = "对方投降";
            u_waiting = true;
            sa_waiting = true;

            sa_restart = true;
            sa_disconnect = true;
        }

        private static void handler_findplayer()
        {
            Debug.Log("findplayer");
            game_reset();
            se_start = true;
            se_nickname = true;
            se_host = true;

            d_selfname = nickname.text;
            u_selfname = true;
            byte head = (byte)HEAD.PLAYERNAME;
            byte[] data = System.Text.Encoding.ASCII.GetBytes(d_selfname);
            set_msg(head, data);
            send();
            msg_r[0] = (byte)HEAD.TEST;
            receive();
        }
        private static void handler_other_playname()
        {
            Debug.Log("other_player");
            char[] name = new char[MSG_LENTH - 1];
            System.Array.Copy(msg_r, 1, name, 0, MSG_LENTH - 1);
            d_othername = new string(name);
            u_othername = true;

            sa_selfname =true;
            sa_othername=true;
            sa_pause=true;
            sa_janken_rock=true;
            sa_janken_scissors=true;
            sa_janken_paper=true;

            se_waiting = true;
        }
        private static void handler_janken_result()
        {
            se_waiting = true;
            Debug.Log("janken_result");
            DATA result = (DATA)msg_r[1];
            switch (result)
            {
                case DATA.JANKEN_DRAW:
                    Debug.Log("janken_resual_draw");
                    sa_janken_rock =true;
                    sa_janken_scissors=true;
                    sa_janken_paper=true;
                    break;
                case DATA.JANKEN_LOSE:
                    Debug.Log("janken_resual_lose");
                    is_gaming = true;
                    chess_other = 1;
                    chess_self = 2;
                    is_turn = false;
                    msg_r[0] = (byte)HEAD.TEST;
                    receive();
                    break;
                case DATA.JANKEN_WIN:
                    Debug.Log("janken_resual_win");
                    is_gaming = true;
                    chess_self = 1;
                    chess_other = 2;
                    is_turn = true;
                    break;
                default:
                    Debug.Log("janken_resual_default");
                    game_reset();
                    close();
                    break;
            }
        }
        private static void handler_other_set()
        {
            Debug.Log("other_set");
            byte[] data = new byte[2];
            System.Array.Copy(msg_r, 1, data, 0, 2);
            int x = (int)data[0];
            int y = (int)data[1];
            chess_board[x, y] = chess_other;
            is_turn = true;
            sa_fx_1 = true;
            se_waiting = true;
        }
        private static void handler_win()
        {
            se_pause = true;
            Debug.Log("win");
            byte data = msg_r[1];
            if (data == (byte)DATA.JANKEN_WIN)
            {
                d_message = "You win!";
                u_message = true;
                sa_message = true;
                is_gaming = false;
                sa_restart = true;
                sa_disconnect = true;
                se_waiting = true;
                msg_r[0] = (byte)HEAD.TEST;
                receive();
            }
            else if (data == (byte)DATA.JANKEN_LOSE)
            {
                int x = (int)msg_r[2];
                int y = (int)msg_r[3];
                chess_board[x, y] = chess_other;
                sa_fx_1 = true;
                d_message = "You lose!";
                u_message = true;
                sa_message = true;
                is_gaming = false;
                sa_restart = true;
                sa_disconnect = true;
                se_waiting = true;
                msg_r[0] = (byte)HEAD.TEST;
                receive();
            }else
            {
                d_message = "未知对局结果，请重开";
                sa_message = true;
                u_message = true;
                se_waiting = true;
                is_gaming = false;
                game_reset();
                close();
            }
        }
        private static void handler_other_disconnect()
        {
            d_message = "对方已断开";
            u_message = true;
            sa_message = true;
            game_reset();
            close();
        }

        public static void game_reset()
        {
            sa_start = true;
            sa_host = true;
            sa_nickname = true;

            se_pause = true;
            se_surrender = true;
            se_restart = true;
            se_disconnect = true;
            se_selfname = true;
            se_othername = true;
            se_waiting = true;
            se_janken = true;
            se_ACK = true;
            sa_fx_1 = false;

            is_gaming = false;
            System.Array.Clear(chess_board, 0, 19 * 19);
        }
        public static void close()
        {
            socket.Shutdown(SocketShutdown.Both);
            socket.Close();
            inited = false;
        }

        public static int chess_self;
        public static int chess_other;

        public static int[,] chess_board;

        public static bool is_turn;

        public static bool is_gaming;

        static GameObject Menu;

        static InputField nickname;
        
        public static bool u_message;
        public static string d_message;
        public static bool u_selfname;
        public static string d_selfname;
        public static bool u_othername;
        public static string d_othername;
        public static bool u_waiting;
        public static string d_waiting;

        public static bool sa_selfname;
        public static bool sa_othername;
        public static bool sa_pause;
        public static bool sa_janken_rock;
        public static bool sa_janken_scissors;
        public static bool sa_janken_paper;
        public static bool sa_message;
        public static bool sa_start;
        public static bool sa_host;
        public static bool sa_nickname;
        public static bool sa_waiting;
        public static bool sa_surrender;
        public static bool sa_restart;
        public static bool sa_disconnect;
        public static bool sa_ACK;
        public static bool sa_fx_1;

        public static bool se_message;
        public static bool se_pause;
        public static bool se_surrender;
        public static bool se_restart;
        public static bool se_disconnect;
        public static bool se_selfname;
        public static bool se_othername;
        public static bool se_waiting;
        public static bool se_ACK;
        public static bool se_start;
        public static bool se_host;
        public static bool se_nickname;
        public static bool se_janken;

        public static int last_x, last_y;
        public static int last_chess;
    }
}