using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
public class onSurrender : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void onclick()
    {
        byte head = (byte)HEAD.SURRENDER;
        byte[] data = { 1 };
        Client.set_msg(head, data);
        Client.send();
        Client.d_waiting = "行动中";
        Client.u_message = true;
        Client.sa_waiting = true;
        this.gameObject.SetActive(false);
        Client.se_restart = true;
        Client.receive();
    }
}
