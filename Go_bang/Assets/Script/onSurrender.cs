﻿using System.Collections;
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
        this.gameObject.SetActive(false);
        Client.receive();
    }
}