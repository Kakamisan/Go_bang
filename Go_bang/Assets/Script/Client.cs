using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace Net
{
    public enum HEAD
    {
        NULL = 0,
        FINDPLAYER,
        JANKEN,
        RESULT,
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
        private static bool is_connected;
        public static void start()
        {
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }
        public static void connect(string ip, int port)
        {
            IPAddress mIp = IPAddress.Parse(ip);
            IPEndPoint ip_end_point = new IPEndPoint(mIp, port);
            try
            {
                socket.Connect(ip_end_point);
                is_connected = true;
                Debug.Log("连接服务器成功");
            }
            catch
            {
                is_connected = false;
                Debug.Log("连接服务器失败");
                return;
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
            
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        public static int chess_sell;
        public static int chess_other;

        public static int[,] chess_board;

        public static bool is_turn;

        public static bool is_gaming;
    }
}