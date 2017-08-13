using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine.SceneManagement;

public class SnakeScript : MonoBehaviour {

    //Direction variable
    Vector2 dir = Vector2.right;
    //List to keep track of Tail
    List<Transform> tail = new List<Transform>();
    //Has the snake eaten an item
    bool atefast = false;
    bool ateslow = false;
    //Tail prefab to be instantiated
    public GameObject tailPrefab;
    private Transform tailExcess;
    //snake speed variable
    float snakeSpeed = 0.2f;
    float maxSnakeSpeed = 0.1f;
    float minSnakeSpeed = 0.3f;

    private AudioSource scoreSFX;

    //Variable to GameManagerScript to increment score etc
    private GameObject gameMGMT;
    private GameManagerScript gameMGMTScript;

    // Use this for initialization
    void Start () {
        //Move the snake object every 300ms
        StartCoroutine(MoveSpeed());
        //InvokeRepeating("Move", 0.3f, 0.3f);
        //Find the gamemanager & it's script so it can be called later
        gameMGMT = GameObject.Find("GameManager");
        gameMGMTScript = gameMGMT.GetComponent<GameManagerScript>();
        scoreSFX = GetComponent<AudioSource>();
	}
	
	// Update is called once per frame
	void Update () {
        //Change direction of movement
        //Each if, has another if nested so that the player can't double back on themselves, this stops the snake-bits colliding with each other and ruining their positional values
        //The user CAN however go left and before the move function is called turn back in on themselves and this will result in their death
        if (Input.GetKey(KeyCode.RightArrow))
        {
            if (dir != Vector2.left)
            {
                dir = Vector2.right;
            }
        }
        else if (Input.GetKey(KeyCode.LeftArrow))
        {
            if (dir != Vector2.right)
            {
                dir = Vector2.left;
            }
        }
        else if (Input.GetKey(KeyCode.UpArrow))
        {
            if (dir != Vector2.down)
            {
                dir = Vector2.up;
            }
        }
        else if (Input.GetKey(KeyCode.DownArrow))
        {
            if (dir != Vector2.up)
            {
                dir = Vector2.down;
            }
        }
    }

    void Move()
    {
        //Save current position, the gap will be here
        Vector2 v = transform.position;

        //Move head into new direction
        transform.Translate(dir*2);

        //Has snake eaten?
        if (atefast)
        {
            //Load prefab
            GameObject g = (GameObject)Instantiate(tailPrefab, v, Quaternion.identity);
            //Keep track of tail in the list
            tail.Insert(0, g.transform);
            //reset the flag
            atefast = false;
            //Incrase the speed of the snake
            if(snakeSpeed > maxSnakeSpeed)
                snakeSpeed -= 0.025f;
            gameMGMTScript.decrementFood();
        }

        else if (ateslow)
        {
            tailExcess = tail[tail.Count - 1];
            //tail.IndexOf(tail.Count - 1);
            tail.RemoveAt(tail.Count-1);
            Destroy(tailExcess.gameObject);
            ateslow = false;
            if (snakeSpeed < minSnakeSpeed)
                snakeSpeed += 0.025f;
            gameMGMTScript.decrementFood();
        }

        //Does a tail exist?
        else if(tail.Count > 0)
        {
            //Move last element to where the head was
            tail.Last().position = v;

            //Add to front of list, remove from back
            tail.Insert(0, tail.Last());
            tail.RemoveAt(tail.Count-1);
        }
    }

    void OnTriggerEnter2D(Collider2D col)
    {
        //Food?
        if(col.name.StartsWith("FoodFast"))
        {
            //Get longer in next move call
            atefast = true;
            //Remove the food
            Destroy(col.gameObject);
            //Call score method
            gameMGMTScript.incrementScore();
            scoreSFX.Play();
        }else if (col.name.StartsWith("FoodSlow"))
        {
            if (tail.Count == 0)
            {
                SceneManager.LoadScene("Menu");
            }
            ateslow = true;
            Destroy(col.gameObject);
            gameMGMTScript.incrementScore();
            scoreSFX.Play();
        }
        else
        {
            //Lose
//          Debug.Log("GotHere");
            SceneManager.LoadScene("Menu");
        }
    }

    IEnumerator MoveSpeed()
    {
        while(true)
        {
            yield return new WaitForSeconds(snakeSpeed);
            Move();
        }
    }

}
