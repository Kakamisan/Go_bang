using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
public class onDisconnect : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void onclick()
    {
        byte head = (byte)HEAD.DISCONNECT;
        Client.set_msg(head, new byte[1]);
        Client.send();
        Client.game_reset();
        Client.close();
    }
}
