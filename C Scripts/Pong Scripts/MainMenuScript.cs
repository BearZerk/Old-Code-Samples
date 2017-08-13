using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MainMenuScript : MonoBehaviour {

	//Menu States
	public enum MenuStates { Main, Options, Audio, Resolution, Player, Play };
	public MenuStates currentState;

	//Menu Panel Objects
	public GameObject mainMenu;
    public GameObject playerMenu;
	public GameObject optionsMenu;
    public GameObject audioMenu;
    public GameObject resolutionMenu;

    public Slider volumeSlider;
    public Dropdown resolutionDropDown;

    //private int[640, 800, 1024, 1152, 1280, 1280, 1280, 1360, 1366, 1600, 1600, 1680] resolutionXArray;
    private int[] resolutionXArray = new int[] { 640, 800, 1024, 1152, 1280, 1280, 1280, 1360, 1366, 1600, 1600, 1680 };
    private int[] resolutionYArray = new int[] { 480, 600, 768, 864, 720, 800, 960, 768, 768, 900, 1024, 1050 };

    //When Script starts
    void Awake() {
		//Main Menu is default
		currentState = MenuStates.Main;   
	}

    //Called every frame
    void Update() {
		//Check menu state
		switch (currentState) {
			case MenuStates.Main:
				//Set active gameobject for main menu
				mainMenu.SetActive(true);
                playerMenu.SetActive(false);
				optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
				break;
            case MenuStates.Player:
                mainMenu.SetActive(false);
                playerMenu.SetActive(true);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Options:
                //Set active gameobject for options menu
                mainMenu.SetActive(false);
                playerMenu.SetActive(false);
                optionsMenu.SetActive(true);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Audio:
                //Set active gameobject for audio menu
                mainMenu.SetActive(false);
                playerMenu.SetActive(false);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(true);
                volumeSlider.value = PlayerPrefs.GetFloat("Volume");
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Resolution:
                //Set active gameobject for resolution menu
                mainMenu.SetActive(false);
                playerMenu.SetActive(false);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(true);
                break;
        }
    }

    //=====================MAIN MENU SECTION===================== 
    //When play is pressed
    public void OnStartGame() {
		Debug.Log ("Pressed Play");
        //Load game afterwards
        //If on Menu Scene load the game, if in the game scene, set the timescale back to normal
        currentState = MenuStates.Player;
	}


	//When options is pressed
	public void OnOptions() {
		Debug.Log ("Pressed Options");
		//Change Menu state (main invisible, Options visible)
		currentState = MenuStates.Options;
	}

    //When exit is pressed
    public void OnExit(){
        Debug.Log("Pressed Exit");
        //If on the Menu Scene exit the game, if in the game scene go back to the main menu
        Application.Quit();
    }

    //=====================PLAYER MENU SECTION===================== 
    public void OnMultiplayer()
    {
        PlayerPrefs.SetString("PlayerMode", "Multi");
        SceneManager.LoadScene("Game");
    }

    public void OnSingleplayer()
    {
        PlayerPrefs.SetString("PlayerMode", "Single");
        SceneManager.LoadScene("Game");
    }

    //=====================OPTION MENU SECTION===================== 
    //When Windowed is pressed
    public void OnResolution() {
		Debug.Log ("Pressed Resolution");
        //Change Resolution Later (in new menu?)
        currentState = MenuStates.Resolution;
	}

    //When audio is pressed
    public void OnAudio()
    {
        Debug.Log("Pressed Audio");
        //Change Menu state (Main invisible, options invisible, audio visible
        currentState = MenuStates.Audio;
    }


	//When Back is pressed
	public void OnBack() {
		Debug.Log ("Pressed Back");
		//Change Menu state (reverse of OnOptions()
		currentState = MenuStates.Main;
	}

    //=====================AUDIO/RESOLUTION MENU SECTION===================== 
    //When Back is pressed in AUDIO OR RESOLUTION
    public void OnOptionsBack()
    {
        Debug.Log("Pressed Options Back");
        //Change Menu state (reverse of OnOptions()
        currentState = MenuStates.Options;
    }

    public void OnVolumeChange()
    {
        Debug.Log("Volume Changed");
        Debug.Log(volumeSlider.value);
        PlayerPrefs.SetFloat("Volume", volumeSlider.value);
    }

    public void OnResolutionChange()
    {
        Screen.SetResolution(resolutionXArray[resolutionDropDown.value], resolutionYArray[resolutionDropDown.value], false);
    }   
}
