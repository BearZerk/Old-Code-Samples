using UnityEngine;
using System.Collections;
using System.IO;

//Script for the player.
//Check every single collision type possible e.g. Health, Coins, Key, Lock(goal) and enemy (redundant as handled in the enemy class)
public class CollisionScript : MonoBehaviour {

	private GameControllerScript gcs;

	public AudioClip coinpickup;

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

	void OnTriggerEnter(Collider other)
	{
		if(other.tag == "Coin")
		{
			Destroy(other.gameObject);
			AudioSource.PlayClipAtPoint(coinpickup, transform.position);
			gcs.levelscore++;
		}

	}
	void OnTriggerStay(Collider other)
	{
		if(other.tag == "Exit" && Input.GetKey(KeyCode.E))
		{
			//Levelvalue for STATIC game in order to replay same 5 levels, comment out for PROCGEN game
			gcs.levelvalue++;
			gcs.levelvalue = gcs.levelvalue % 5;

			gcs.levelwriter++;
			gcs.totalscore += gcs.levelscore;
			gcs.totaltime += gcs.leveltime;

			PlayerPrefs.SetInt("Level Value", gcs.levelvalue);
			PlayerPrefs.SetInt("Level Writer", gcs.levelwriter);
			PlayerPrefs.SetInt("Total Score", gcs.totalscore);
			PlayerPrefs.SetInt("Total Time", (int)gcs.totaltime);

			if(!Directory.Exists("Play_Data_B"))
			{
				Directory.CreateDirectory("Play_Data_B");
			}

			using(StreamWriter sw = File.CreateText("Play_Data_B/Level_" + gcs.levelwriter + ".txt"))
			{
				sw.WriteLine("Level Score = " + gcs.levelscore);
				sw.WriteLine("Total Score = " + gcs.totalscore);
				sw.WriteLine("Level Time = " + gcs.leveltime);
				sw.WriteLine("Total Time = " + gcs.totaltime);
				sw.WriteLine("Skips = " + gcs.skips);
				sw.Close();
			}

			//STATIC LEVEL LOADING
			Application.LoadLevel(gcs.levelvalue+1);


			//PROCEDURAL GENREATION LEVEL LOADING
			//Application.LoadLevel(Application.LoadedLevel);
		}
	}
}