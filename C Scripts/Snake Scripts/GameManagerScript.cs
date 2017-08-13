using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class GameManagerScript : MonoBehaviour {

    //private variable for keeping Score
    public int score = 0;
    public int foodCount = 0;
    public bool gameMode;

    void Start()
    {
        if (PlayerPrefs.GetString("Game Mode") == "Extended")
            gameMode = true;
    }

    public void incrementScore()
    {
        score += 10;
    }

    public void incrementFood()
    {
        foodCount++;
        if (gameMode)
        {
            if (getFoodCount() > 10)
                SceneManager.LoadScene("Menu");
        }
    }

    public void decrementFood()
    {
        foodCount--;
    }

    public int getFoodCount()
    {
        return foodCount;
    }
}
