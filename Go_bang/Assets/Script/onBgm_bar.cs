using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class onBgm_bar : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    public void onvc()
    {
        bgm.volume = this.gameObject.GetComponent<Slider>().value;
    }
    public AudioSource bgm;
}
