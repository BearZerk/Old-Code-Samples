using UnityEngine;
using System.Collections;

public class SpawnFoodScript : MonoBehaviour {

    //Food prefab, assigned in inspector
    public GameObject foodPrefabFast;
    public GameObject foodPrefabSlow;

    //Borders, assinged in inspector, food to be instantiated within them
    public GameObject borderTop;
    public GameObject borderBottom;
    public GameObject borderLeft;
    public GameObject borderRight;

    private Vector2 spawnPoint;
    private Vector3 boxChecker = Vector3.zero;

    //Variable to GameManagerScript to increment score etc
    private GameObject gameMGMT;
    private GameManagerScript gameMGMTScript;

    // Use this for initialization
    void Start () {
        //Call Spawn function every few seconds via InvokeREPEATING
        //Spawn food every 4 seconds starting after 3 seconds.
        InvokeRepeating("Spawn", 3, 4);

        gameMGMT = GameObject.Find("GameManager");
        gameMGMTScript = gameMGMT.GetComponent<GameManagerScript>();
    }

    //Spawn a piece of food between the border positions
    void Spawn()
    {
        //NB by using the INT values for the +Spawn/Random values, the x & y positions are rounded.
        int xSpawn = 1;
        int ySpawn = 1;

        //While x & y spawn values are not even, keep re-making the value. 
        //Due to the doubling of the size of the snake, food & walls collisions only work on even values
        while (!isEven(xSpawn) || !isEven(ySpawn))
        {
            //Check if X or Y isn't even yet, then re-instantiate a valid value for them if not
            if(!isEven(xSpawn))
                xSpawn = (int)Random.Range(borderLeft.transform.position.x + (0.5f * borderLeft.GetComponent<Collider2D>().bounds.size.x), borderRight.transform.position.x - (0.5f * borderRight.GetComponent<Collider2D>().bounds.size.x));
            if(!isEven(ySpawn)) 
                ySpawn = (int)Random.Range(borderTop.transform.position.y - (0.5f * borderTop.GetComponent<Collider2D>().bounds.size.y), borderBottom.transform.position.y + (0.5f * borderBottom.GetComponent<Collider2D>().bounds.size.y));

            //Set where we spawn food to the vector values created
            spawnPoint = new Vector2(xSpawn, ySpawn);
            //If the vector values are already taken up my part of the snake/another piece of food, re-roll the values 
            if (Physics.CheckBox(spawnPoint, boxChecker))
            {
                xSpawn = 1;
                ySpawn = 2;
            }
        }

        //If in the extended game mode, spawn both types of food
        if (gameMGMTScript.gameMode)
        {
            if (Mathf.RoundToInt(Random.value) == 0)
                //Actually instantiate the food prefab
                Instantiate(foodPrefabFast, new Vector2(xSpawn, ySpawn), Quaternion.identity);
            else
                Instantiate(foodPrefabSlow, new Vector2(xSpawn, ySpawn), Quaternion.identity);
            //Quaternion just deals with rotation, identity means the default rotation.
        }
        //If in normal game mode only spawn the simple food item
        else
        {
            Instantiate(foodPrefabFast, new Vector2(xSpawn, ySpawn), Quaternion.identity);
        }
        gameMGMTScript.incrementFood();
    }

    bool isEven(int testValue)
    {
        if (testValue % 2 == 0)
            return true;
        return false;
    }
}
