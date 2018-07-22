using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Net;
public class onACK : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void onclick()
    {
        Client.set_msg((byte)HEAD.ACK, new byte[1]);
        this.gameObject.SetActive(false);
        Client.send();
        Client.receive();
    }
}
