using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameManagementScript : MonoBehaviour {

    //Private values for left & right scores
    private int leftScore;
    private int rightScore;
    //public object assigned in the inspector of the prefab that needs to be instantiated in 'SetScene' procedure
    public GameObject ball;
    //public integer variable to determine basically if ANYONE has scored yet, if not the ball is randomly served instead of served to the loser of the point
    public int totalScore;
    //Create a bool for if the last goal was scored by which side. 0 = Left, 1 = Right. Therefore loser of the point get's to 'serve'
    public bool rScore;
    //Create text variables to interact with the score UI
    public Text leftScoreText;
    public Text rightScoreText;
    //Create aiRacket object so I can call when to re-set the ball reference it has when a new ball is created.
    public GameObject aiRacket;
    public AIScript aiRacketScript;
    public GameObject playerRacket;


    //At the beginning of the game set all variables to 0/false as no-one has scored and the game shouldn't be paused.
    void Start() {

        if (PlayerPrefs.GetString("PlayerMode") == "Single")
        {
            Instantiate(aiRacket, new Vector2(5, 0), Quaternion.identity);
            aiRacketScript = GameObject.Find("AIRacket(Clone)").GetComponent<AIScript>();
            //aiRacket.GetComponent<AIScript>();
            Invoke("SetAIScene", 1.0f);
        }
        else
        {
            Instantiate(playerRacket, new Vector2(5, 0), Quaternion.identity);
            SetPlayerScene();
        }

        leftScore = 0;
        rightScore = 0;
        totalScore = leftScore + rightScore;
        UIUpdate();
    }

    //If the right player has scored, increment the score and totalscore for the ball serving purposes
    //Set the rScore bool to true so it gets served left this time, and invoke the function SetScene in 1 second
    public void RightScored() {
        rightScore++;
        UIUpdate();
        totalScore += rightScore;
        rScore = true;
        if (PlayerPrefs.GetString("PlayerMode") == "Single")
            Invoke("SetAIScene", 1.0f);
        else
            Invoke("SetPlayerScene", 1.0f);
    }

    //See RightScored, and change all rights to lefts and vice versa
    public void LeftScored() {
        leftScore++;
        UIUpdate();
        totalScore += leftScore;
        rScore = false;
        if (PlayerPrefs.GetString("PlayerMode") == "Single")
            Invoke("SetAIScene", 1.0f);
        else
            Invoke("SetPlayerScene", 1.0f);
    }

    //Set a bug catching error of if the ball falls out of bounds and is therefore deleted from the scene
    public void OutOfBounds() {
        if (PlayerPrefs.GetString("PlayerMode") == "Single")
            Invoke("SetAIScene", 1.0f);
        else
            Invoke("SetPlayerScene", 1.0f);
    }

    void SetAIScene() {
		aiRacketScript.ball = (GameObject) Instantiate (ball, new Vector2 (0, 0), Quaternion.identity);
	}

    void SetPlayerScene()
    {
        Instantiate(ball, new Vector2(0, 0), Quaternion.identity);
    }

	void UIUpdate () {
		leftScoreText.text = leftScore.ToString ();
		rightScoreText.text = rightScore.ToString ();
	}
}
