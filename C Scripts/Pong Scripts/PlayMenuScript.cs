using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayMenuScript : MonoBehaviour
{

    //Menu States
    public enum MenuStates { Main, Options, Audio, Resolution, Play };
    public MenuStates currentState;

    //Menu Panel Objects
    public GameObject mainMenu;
    public GameObject optionsMenu;
    public GameObject audioMenu;
    public GameObject resolutionMenu;

    public Slider volumeSliderPlay;
    public Dropdown resolutionDropDownPlay;

    //private int[640, 800, 1024, 1152, 1280, 1280, 1280, 1360, 1366, 1600, 1600, 1680] resolutionXArray;
    private int[] resolutionXArrayPlay = new int[] { 640, 800, 1024, 1152, 1280, 1280, 1280, 1360, 1366, 1600, 1600, 1680 };
    private int[] resolutionYArrayPlay = new int[] { 480, 600, 768, 864, 720, 800, 960, 768, 768, 900, 1024, 1050 };


    private bool paused;

    //When Script starts
    void Awake()
    {
        //Play Menu is default
        currentState = MenuStates.Play;
        AudioListener.volume = PlayerPrefs.GetFloat("Volume");
    }

    //Called every frame
    void Update()
    {
        //Check menu state
        switch (currentState)
        {
            case MenuStates.Main:
                //Set active gameobject for main menu
                mainMenu.SetActive(true);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Options:
                //Set active gameobject for options menu
                mainMenu.SetActive(false);
                optionsMenu.SetActive(true);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Audio:
                //Set active gameobject for audio menu
                mainMenu.SetActive(false);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(true);
                volumeSliderPlay.value = PlayerPrefs.GetFloat("Volume");
                resolutionMenu.SetActive(false);
                break;
            case MenuStates.Resolution:
                //Set active gameobject for resolution menu
                mainMenu.SetActive(false);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(true);
                break;
            case MenuStates.Play:
                mainMenu.SetActive(false);
                optionsMenu.SetActive(false);
                audioMenu.SetActive(false);
                resolutionMenu.SetActive(false);
                break;
        }

        if (Input.GetKeyUp(KeyCode.P))
        {
            if (paused)
            {
                currentState = MenuStates.Play;
                Time.timeScale = 1.0f;
                paused = false;
            }
            else
            {
                currentState = MenuStates.Main;
                Time.timeScale = 0.0f;
                paused = true;
            }
        }

    }

    //=====================MAIN MENU SECTION===================== 
    //When play is pressed
    public void OnStartGame()
    {
        Debug.Log("Pressed Play");
        //Load game afterwards
        //If on Menu Scene load the game, if in the game scene, set the timescale back to normal
        Time.timeScale = 1;
        currentState = MenuStates.Play;
    }

    //When options is pressed
    public void OnOptions()
    {
        Debug.Log("Pressed Options");
        //Change Menu state (main invisible, Options visible)
        currentState = MenuStates.Options;
    }

    //When exit is pressed
    public void OnExit()
    {
        Debug.Log("Pressed Exit");
        SceneManager.LoadScene("Menu");
        Time.timeScale = 1.0f;
        currentState = MenuStates.Main;
    }

    //=====================OPTION MENU SECTION===================== 
    //When Windowed is pressed
    public void OnResolution()
    {
        Debug.Log("Pressed Resolution");
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
    public void OnBack()
    {
        Debug.Log("Pressed Back");
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
        Debug.Log(volumeSliderPlay.value);
        PlayerPrefs.SetFloat("Volume", volumeSliderPlay.value);
        AudioListener.volume = volumeSliderPlay.value;
    }

    public void OnResolutionChange()
    {
        Screen.SetResolution(resolutionXArrayPlay[resolutionDropDownPlay.value], resolutionYArrayPlay[resolutionDropDownPlay.value], false);
    }
}
