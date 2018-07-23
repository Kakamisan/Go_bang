using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
public class onRestart : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void onclick()
    {
        byte head = (byte)HEAD.RESTART;
        Client.set_msg(head, new byte[1]);
        Client.send();
        Client.d_waiting = "行动中";
        Client.u_message = true;
        Client.sa_waiting = true;
        this.gameObject.SetActive(false);
        Client.receive();
    }
}
