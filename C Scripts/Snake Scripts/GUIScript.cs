using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class GUIScript : MonoBehaviour {

    //Bool to know when to pause the game & draw new menu options
    public bool paused;
    //Bool to know when in game or in menu
    public bool inGame;
    //INteraction with GameManager
    GameObject gameManager;
    GameManagerScript gameManagerScript;
    //GUISkin to model all the buttons and stuff, assinged in Inspector
    public GUISkin myskin;

    void Start()
    {

        //If it's the Game
        if (SceneManager.GetActiveScene().buildIndex == 1)
        {
            paused = false;
            inGame = true;
            gameManager = GameObject.Find("GameManager");
            gameManagerScript = gameManager.GetComponent<GameManagerScript>();
        }
        //If it's not (i.e. Menu)
        else if (SceneManager.GetActiveScene().buildIndex == 0)
        {
            paused = false;
            inGame = false;
        }

    }

    void Update()
    {
        //If the key UP value is P, and it ISN'T paused, then pause
        //If the key UP value is P, and it IS paused, then unpause
        if (Input.GetKeyUp(KeyCode.P))
        {
            if(paused)
            {
                Time.timeScale = 1.0f;
                paused = false;
            }
            else
            {
                Time.timeScale = 0.0f;
                paused = true;
            }
        }
    }

    void OnGUI()
    {
        GUI.skin = myskin;

        //If at the mainMenu
        if (!inGame)
        {
            //Play Button
            if (GUI.Button(new Rect(((Screen.width / 2) - Screen.width / 4), ((Screen.height / 2) + Screen.height / 15), (Screen.width / 5), (Screen.height / 10)), "Play Normal"))
            {
                PlayerPrefs.SetString("Game Mode", "Normal");
                inGame = true;
                SceneManager.LoadScene("Game");
            }
            if (GUI.Button(new Rect(((Screen.width / 2) + Screen.width / 20), ((Screen.height / 2) + Screen.height / 15), (Screen.width / 5), (Screen.height / 10)), "Play Extended"))
            {
                PlayerPrefs.SetString("Game Mode", "Extended");
                inGame = true;
                SceneManager.LoadScene("Game");
            }
            //Volume Slider
            AudioListener.volume = GUI.HorizontalSlider(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) + Screen.height / 4), (Screen.width / 5), (Screen.height / 10)), AudioListener.volume, 0.0f, 10.0f);    
            GUI.Label(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) + Screen.height / 4), (Screen.width / 5), (Screen.height / 10)), "Volume");
            //Quit Button
            if (GUI.Button(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) + Screen.height / 3), (Screen.width / 5), (Screen.height / 10)), "Quit"))
            {
                Application.Quit();
            }
        }
        //If actually inGame
        else if (inGame)
        {
            GUI.Label(new Rect(((Screen.width/2) - Screen.width/25), ((Screen.height / 12)- Screen.height/30), (Screen.width/10), (Screen.height/25)), gameManagerScript.score.ToString());
            if (paused)
            {
                if (GUI.Button(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) - Screen.height / 20), (Screen.width / 5), (Screen.height / 10)), "Play"))
                {
                    Time.timeScale = 1.0f;
                    paused = false;
                }
                //Volume Slider
                AudioListener.volume = GUI.HorizontalSlider(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) + Screen.height / 15), (Screen.width / 5), (Screen.height / 10)), AudioListener.volume, 0.0f, 10.0f);
                GUI.Label(new Rect(((Screen.width / 2) - Screen.width/10), ((Screen.height / 2) + Screen.height / 15), (Screen.width / 5), (Screen.height / 10)), "Volume");
                //Quit Button
                if (GUI.Button(new Rect(((Screen.width / 2) - Screen.width / 10), ((Screen.height / 2) + Screen.height / 5), (Screen.width / 5), (Screen.height / 10)), "Quit"))
                {
                    paused = false;
                    inGame = false;
                    Time.timeScale = 1.0f;
                    SceneManager.LoadScene("Menu");
                }
            }
        }
    }
}
