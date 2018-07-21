using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnMessage : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnEnable()
    {
        Invoke("disActive", 3.0f);
    }

    void disActive()
    {
        this.gameObject.SetActive(false);
    }
}
