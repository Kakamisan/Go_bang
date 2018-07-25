using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class onFx_bar : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    public void onvc()
    {
        fx_1.volume = this.gameObject.GetComponent<Slider>().value;
    }
    public AudioSource fx_1;
}
