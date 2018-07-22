using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;

public class chess_set : MonoBehaviour {

    const int board_size = 19;

    public GameObject left_top;
    public GameObject right_top;
    public GameObject left_bom;
    public GameObject right_bom;

    Vector3 LT;
    Vector3 RT;
    Vector3 LB;
    Vector3 RB;
    
    public Sprite white;
    public Sprite black;

    public Camera cam;

    float grid_x;
    float grid_y;
    float grid;
    
    Vector2[,] chess_pos;

    bool chess_ready;
    Vector2 chess_ready_pos;
    Vector2 point;
    bool point_down;

    // Use this for initialization
    void Start ()
    {
        Client.chess_board = new int[board_size, board_size];
        chess_pos = new Vector2[board_size, board_size];
        LT = cam.WorldToScreenPoint(left_top.transform.position);
        RT = cam.WorldToScreenPoint(right_top.transform.position);
        LB = cam.WorldToScreenPoint(left_bom.transform.position);
        RB = cam.WorldToScreenPoint(right_bom.transform.position);
        grid_x = (RT.x - LT.x) / (board_size - 1);
        grid_y = (LT.y - LB.y) / (board_size - 1);
        grid = Mathf.Min(grid_x, grid_y);
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                chess_pos[i, j] = new Vector2(LT.x + grid_x * j, LT.y - grid_y * i);
            }
        }
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (Client.is_turn && Client.is_gaming)
        {
            point = Input.mousePosition;
            if (Input.GetMouseButtonDown(0)) point_down = true;

            for (int i = 0; i < board_size; i++)
            {
                for (int j = 0; j < board_size; j++)
                {
                    if (Client.chess_board[i, j] == 0 && Distance(point, chess_pos[i, j]) < (grid_x + grid_y) / 4)
                    {
                        chess_ready = true;
                        chess_ready_pos = chess_pos[i, j];
                        if (Input.GetMouseButtonUp(0) && point_down)
                        {
                            Client.chess_board[i, j] = Client.chess_self;
                            point_down = false;
                            byte head = (byte)HEAD.SET;
                            byte[] data = new byte[2];
                            data[0] = (byte)i;
                            data[1] = (byte)j;
                            Client.set_msg(head, data);
                            Client.send();
                            Client.is_turn = false;
                            Client.sa_waiting = true;
                            Client.d_waiting = "行动中。。。";
                            Client.u_waiting = true;
                            Client.receive();
                        }
                        return;
                    }
                    else
                    {
                        chess_ready = false;
                        return;
                    }
                }
            }
        }
	}

    float Distance(Vector3 point,Vector2 other)
    {
        return Mathf.Sqrt(Mathf.Pow(point.x - other.x, 2) + Mathf.Pow(point.y - other.y, 2));
    }

    void OnGUI()
    {
        for(int i = 0; i < board_size; i++)
        {
            for(int j = 0; j < board_size; j++)
            {
                if (Client.chess_board[i, j] == 1)
                {
                    GUI.DrawTexture(new Rect(chess_pos[i, j].x - grid_x / 2+1, Screen.height-chess_pos[i, j].y - grid_y / 2+1, grid-2, grid-2), white.texture);
                }
                if (Client.chess_board[i, j] == 2)
                {
                    GUI.DrawTexture(new Rect(chess_pos[i, j].x - grid_x / 2 + 1, Screen.height - chess_pos[i, j].y - grid_y / 2 + 1, grid - 2, grid - 2), black.texture);
                }
            }
        }
        if (Client.chess_self == 1 && chess_ready)
        {
            GUI.DrawTexture(new Rect(chess_ready_pos.x - grid_x / 2 + 1, Screen.height - chess_ready_pos.y - grid_y / 2 + 1, grid - 2, grid - 2), white.texture);
        }else if (Client.chess_self == 2 && chess_ready)
        {
            GUI.DrawTexture(new Rect(chess_ready_pos.x - grid_x / 2 + 1, Screen.height - chess_ready_pos.y - grid_y / 2 + 1, grid - 2, grid - 2), black.texture);
        }
    }
}
