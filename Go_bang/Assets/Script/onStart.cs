using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text.RegularExpressions;
using Net;

public class onStart : MonoBehaviour {

    const int port = 20013;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public InputField text_ip;
    public InputField text_nick;
    public Text message;

    public void onclick()
    {
        if (text_nick.text == "" || text_ip.text == "")
        {
            message.text = "不能为空";
            message.gameObject.SetActive(true);
            return;
        }
        Regex reg = new Regex(@"(?=(\b|\D))(((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))\.){3}((\d{1,2})|(1\d{1,2})|(2[0-4]\d)|(25[0-5]))(?=(\b|\D))");
        if (!reg.IsMatch(text_ip.text))
        {
            message.text = "请检查主机ip";
            message.gameObject.SetActive(true);
            return;
        }
        Regex reg2 = new Regex(@"^[_a-zA-Z0-9]{1,15}$");
        if (!reg2.IsMatch(text_nick.text))
        {
            message.text = "请用字母与数字";
            message.gameObject.SetActive(true);
            return;
        }
        text_nick.gameObject.SetActive(false);
        text_ip.gameObject.SetActive(false);
        this.gameObject.SetActive(false);
        Client.connect(text_ip.text, port);
        Client.receive();
    }
}
