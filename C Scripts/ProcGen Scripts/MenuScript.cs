using UnityEngine;
using System.Collections;

public class MenuScript : MonoBehaviour {

	//Main menu script, same difficutly as ReturnScript except the added button beginning the actual game!
	int buttonheight = 70;
	int buttonwidth = 120;
	public GUISkin myskin = null;

	private GameControllerScript gcs;

	void Start()
	{
		GameObject gameControllerObject = GameObject.FindWithTag ("GameController");
		
		if(gameControllerObject != null)
		{
			gcs = gameControllerObject.GetComponent<GameControllerScript>();
		}
		if(gcs == null)
		{
			Debug.Log("Cannot find 'GameController' script");
		}
	}

	void OnGUI()
	{
		GUI.skin = myskin;
		if(GUI.Button(new Rect (Screen.width/2-buttonwidth/2, Screen.height*0.25f-buttonheight/2, buttonwidth, buttonheight), "Play"))
		{
			Application.LoadLevel(gcs.levelvalue+1);
		}

		if(GUI.Button(new Rect (Screen.width/2-buttonwidth/2, Screen.height*0.5f-buttonheight/2, buttonwidth, buttonheight), "Info"))
		{
			Application.LoadLevel("Info");
		}
	} 

	void Update()
	{
		if(Input.GetKey (KeyCode.Escape))
		{
			Application.Quit();
		}
		PlayerPrefs.SetInt ("Level Value", 0);
		PlayerPrefs.SetInt("Level Writer", 0);
		PlayerPrefs.SetInt("Total Score", 0);
		PlayerPrefs.SetInt("Total Time", 0);
		PlayerPrefs.SetInt("Skips", 0);
	}
}
