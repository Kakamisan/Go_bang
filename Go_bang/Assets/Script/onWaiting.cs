using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class onWaiting : MonoBehaviour {

    public Text waiting;
    string first_str;
	// Use this for initialization
	void Start () {
        //waiting = this.gameObject.GetComponent<Text>();
        Invoke("change2f", 0.6f);
    }
	
	// Update is called once per frame
	void Update () {
		
	}

    void OnEnable()
    {
        first_str = waiting.text;
    }

    void change2f()
    {
        waiting.text = first_str + "。";
        Invoke("change2s", 0.6f);
    }
    void change2s()
    {
        waiting.text = first_str + "。。";
        Invoke("change2t", 0.6f);
    }
    void change2t()
    {
        waiting.text = first_str + "。。。";
        Invoke("change2f", 0.6f);
    }
}
