using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
using UnityEngine.UI;
public class onPaper : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    public void onclick()
    {
        byte head = (byte)HEAD.JANKEN;
        byte[] data = new byte[Client.MSG_LENTH - 1];
        data[0] = (byte)DATA.JANKEN_PAPER;
        this.gameObject.SetActive(false);
        b2.gameObject.SetActive(false);
        b3.gameObject.SetActive(false);

        Client.set_msg(head, data);
        Client.send();
        Client.d_waiting = "行动中";
        Client.u_message = true;
        Client.sa_waiting = true;
        Client.receive();
    }
    public Button b2, b3;
}
