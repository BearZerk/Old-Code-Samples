﻿using UnityEngine;
using System.Collections;

//general script to attach to several scenes to allow return to the main menu.
public class ReturnScript : MonoBehaviour {
	
	int buttonheight = 70;
	int buttonwidth = 120;
	public GUISkin myskin = null;
	
	void OnGUI()
	{
		GUI.skin = myskin;
		if(GUI.Button(new Rect (Screen.width/2-buttonwidth/2, Screen.height*0.75f-buttonheight/2, buttonwidth, buttonheight), "Menu"))
		{
			Application.LoadLevel("Menu");
		}
	} 

	void Update()
	{
		if(Input.GetKey (KeyCode.Escape))
		{
			Application.LoadLevel("Menu");
		}
	}
}