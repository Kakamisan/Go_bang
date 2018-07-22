using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class onPause : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void onclick()
    {
        if (enable_)
        {
            surrender.gameObject.SetActive(false);
            restart.gameObject.SetActive(false);
            disconnect.gameObject.SetActive(false);
            enable_ = false;
        }else
        {
            surrender.gameObject.SetActive(true);
            restart.gameObject.SetActive(true);
            disconnect.gameObject.SetActive(true);
            enable_ = true;
        }
    }

    void OnEnable()
    {
        surrender.gameObject.SetActive(false);
        restart.gameObject.SetActive(false);
        disconnect.gameObject.SetActive(false);
        enable_ = false;
    }
    public Button surrender;
    public Button restart;
    public Button disconnect;
    bool enable_ = false;
}
