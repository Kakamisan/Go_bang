using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
using UnityEngine.UI;

public class Main : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (Client.u_selfname)
        {
            selfname.text = Client.d_selfname;
            Client.u_selfname = false;
        }
        if (Client.u_othername)
        {
            othername.text = Client.d_othername;
            Client.u_othername = false;
        }
        if (Client.sa_selfname)
        {
            selfname.gameObject.SetActive(true);
            Client.sa_selfname = false;
        }
        if (Client.sa_othername)
        {
            othername.gameObject.SetActive(true);
            Client.sa_othername = false;
        }
        if (Client.sa_pause)
        {
            pause.gameObject.SetActive(true);
            Client.sa_pause = false;
        }
        if (Client.sa_janken_rock)
        {
            janken_rock.gameObject.SetActive(true);
            Client.sa_janken_rock = false;
        }
        if (Client.sa_janken_scissors)
        {
            janken_scissors.gameObject.SetActive(true);
            Client.sa_janken_scissors = false;
        }
        if (Client.sa_janken_paper)
        {
            janken_paper.gameObject.SetActive(true);
            Client.sa_janken_paper = false;
        }
        if (Client.u_message)
        {
            message.text = Client.d_message;
            Client.u_message = false;
        }
        if (Client.sa_message)
        {
            message.gameObject.SetActive(true);
            Client.sa_message = false;
        }
        if (Client.sa_start)
        {
            start.gameObject.SetActive(true);
            Client.sa_start = false;
        }
        if (Client.sa_host)
        {
            host.gameObject.SetActive(true);
            Client.sa_host = false;
        }
        if (Client.sa_nickname)
        {
            nickname.gameObject.SetActive(true);
            Client.sa_nickname = false;
        }
        if (Client.se_disconnect)
        {
            disconnect.gameObject.SetActive(false);
            Client.se_disconnect = false;
        }
        if (Client.se_othername)
        {
            othername.gameObject.SetActive(false);
            Client.se_othername = false;
        }
        if (Client.se_pause)
        {
            pause.gameObject.SetActive(false);
            Client.se_pause = false;
        }
        if (Client.se_restart)
        {
            restart.gameObject.SetActive(false);
            Client.se_restart = false;
        }
        if (Client.se_selfname)
        {
            selfname.gameObject.SetActive(false);
            Client.se_selfname = false;
        }
        if (Client.se_surrender)
        {
            surrender.gameObject.SetActive(false);
            Client.se_surrender = false;
        }
        if (Client.sa_waiting)
        {
            waiting.gameObject.SetActive(true);
            Client.sa_waiting = false;
        }
        if (Client.se_waiting)
        {
            waiting.gameObject.SetActive(false);
            Client.se_waiting = false;
        }
        if (Client.u_waiting)
        {
            waiting.text = Client.d_waiting;
            Client.u_waiting = false;
        }
        if (Client.sa_restart)
        {
            restart.gameObject.SetActive(true);
            Client.sa_restart = false;
        }
        if (Client.sa_disconnect)
        {
            disconnect.gameObject.SetActive(true);
            Client.sa_disconnect = false;
        }
        if (Client.sa_ACK)
        {
            ACK.gameObject.SetActive(true);
            Client.sa_ACK = false;
        }
        if (Client.se_ACK)
        {
            ACK.gameObject.SetActive(false);
            Client.se_ACK = false;
        }
        if (Client.se_start)
        {
            start.gameObject.SetActive(false);
            Client.se_start = false;
        }
        if (Client.se_host)
        {
            host.gameObject.SetActive(false);
            Client.se_host = false;
        }
        if (Client.se_nickname)
        {
            nickname.gameObject.SetActive(false);
            Client.se_nickname = false;
        }
	}

    public Text selfname;
    public InputField nickname;
    public Text othername;
    public Button pause;
    public Button janken_rock;
    public Button janken_scissors;
    public Button janken_paper;
    public Text message;
    public Button start;
    public InputField host;
    public Button disconnect;
    public Button restart;
    public Button surrender;
    public Text waiting;
    public Button ACK;
}
