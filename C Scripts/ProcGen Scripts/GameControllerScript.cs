using UnityEngine;
using System.Collections;

//GameController, used  for drawing the score and current state of if the player has picked up the key in game or not.
//this script is highly used across otehr scripts.
public class GameControllerScript : MonoBehaviour {

	public bool pause = false;
	public string level;

	public int tl, tr, bl, br;
	public double leveltime, totaltime;
	public int levelscore, totalscore, skips, levelwriter, levelvalue;

	public Texture coin, clock;

	void OnGUI()
	{
		GUI.DrawTexture (new Rect (25, -5, coin.height, coin.width), coin, ScaleMode.ScaleToFit, true, 0);
		GUI.DrawTexture (new Rect (115, 10, clock.height*0.25f, clock.width*0.25f), clock, ScaleMode.ScaleToFit, true, 0);

		GUI.contentColor = Color.black;
		GUI.Label (new Rect (55, 18, 20, 40), ""+levelscore);
		GUI.Label (new Rect (125, 18, 20, 40), ""+(int)leveltime);
	}

	void Update()
	{
		if(Input.GetKeyUp(KeyCode.P))
		{
			if(pause)
			{
				pause = false;
				Time.timeScale = 1;
			}
			else
			{
				pause = true;
				Time.timeScale = 0;
			}
		}
		
		if(Input.GetKey (KeyCode.Escape))
		{
			PlayerPrefs.SetInt ("Level Value", 0);
			PlayerPrefs.SetInt("Level Writer", 0);
			PlayerPrefs.SetInt("Total Score", 0);
			PlayerPrefs.SetInt("Total Time", 0);
			PlayerPrefs.SetInt("Skips", 0);
			Application.LoadLevel("Menu");
		}

		if(Input.GetKey (KeyCode.R))
		{
			skips++;
			Application.LoadLevel(Application.loadedLevel);
		}

		if(!pause)
		{
			leveltime += Time.deltaTime;
		}
	}

	void Start(){
		levelscore = 0;
		leveltime = 0;

		levelwriter = PlayerPrefs.GetInt ("Level Writer");
		totalscore = PlayerPrefs.GetInt ("Total Score");
		totaltime = PlayerPrefs.GetInt ("Total Time");
		skips = PlayerPrefs.GetInt ("Skips");

		if(totaltime > 600)
		{
			Application.LoadLevel("End");
		}


		//STATIC GAME LEVEL VALUE
		levelvalue = PlayerPrefs.GetInt ("Level Value");

		level = Application.loadedLevelName;
/*
 * 		PROCEDRUAL GENERATION USING TIMED SEED
		Random.seed = System.DateTime.Now.Millisecond;

		tl = Mathf.FloorToInt(Random.value*10);
		tr = Mathf.FloorToInt(Random.value*10);

		while((tl < 5 && tr < 5) || (tl > 4 && tr > 4))
		{
			tr = Mathf.FloorToInt(Random.value*10);
		}

		bl = Mathf.FloorToInt(Random.value*10);
		br = Mathf.FloorToInt(Random.value*10);

		while((bl < 5 && br < 5) || (bl > 4 && br > 4))
		{
			br = Mathf.FloorToInt(Random.value*10);
		}


		Instantiate (Resources.Load("TopLeft/" + tl), new Vector3(0, 0, 0), Quaternion.identity);
		Instantiate (Resources.Load("TopRight/" + tr), new Vector3(5, 0, 0), Quaternion.identity);
		Instantiate (Resources.Load("BottomLeft/" + bl), new Vector3 (0, -5, 0), Quaternion.identity);
		Instantiate (Resources.Load("BottomRight/" + br), new Vector3 (5, -5, 0), Quaternion.identity);
*/
	}
}