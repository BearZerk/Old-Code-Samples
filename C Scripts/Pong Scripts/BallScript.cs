using UnityEngine;
using System.Collections;

public class BallScript : MonoBehaviour {

	//Create magnitude to be used for Velocity
	private float speed = 5.0f;
	//Create strings for the Racket Tag, and then further string to identify which racket
	private string racket = "Racket";
	private string rLeft = "RacketLeft";
	//Create a vector to be altered for when colliding with rackets
	private Vector2 dir;
	//Create strings for the Goal tag and then further string to identify which goal
	private string goal = "Goal";
	private string gLeft = "GoalLeft";
	//Create an object that will be the game manager so we can interact with it to increase score etc.
	private GameObject gameM;
	//Create a Gamemanager script object so that interaction with the gamemanager is simpler to code.
	private GameManagementScript gameMS;
	//Set a private value to determine which side to serve to 'randomly' for the first serve of the game.
	private float randomServe;
	//Set Audio Effect for bouncing
	private AudioSource bounce;


	// Use this for initialization
	void Start () {
		//Create an initial velocity
		//Set private variables of GameManager & GameManagementScript
		gameM = GameObject.Find ("GameManager");
		gameMS = gameM.GetComponent<GameManagementScript> ();
		//Set up randomserve value to either 1 or 0.
		randomServe = Mathf.Round (Random.value);
		//Set up audio bounce value
		bounce = GetComponent<AudioSource> ();

		//If the score isn't 0 and the Right player has just scored, serve the new ball left, otherwise serve right
		if (gameMS.totalScore != 0) {
			if (gameMS.rScore) {
				GetComponent<Rigidbody2D> ().velocity = Vector2.left * speed;
			} else {
				GetComponent<Rigidbody2D> ().velocity = Vector2.right * speed;
			}
		//Otherwise if there isn't a score yet, but randomscore has been set to 1 not 0, serve it right, otherwise left.
		} else {
			if(randomServe == 1) {
				GetComponent<Rigidbody2D> ().velocity = Vector2.right * speed;
			} else {
				GetComponent<Rigidbody2D> ().velocity = Vector2.left * speed;
			}
		}
	}

	//When this object collides with another object ('Col') run through this method.
	//Called when the colliders BEGIN to touch, not when they've stopped (On...Exit) and not for every frame they touch (On...Stay)
	void OnCollisionEnter2D(Collision2D col) {
		//If the ball has just hit a racket
		if (col.gameObject.tag == racket) {
			//Pass ball position, racket position, and rackets height
			float y = hitFactor(transform.position, col.transform.position, col.collider.bounds.size.y);
			//If the racket in question is the left one ... else it's the right one ...
			if (col.gameObject.name == rLeft){
				//Normalized keeps the magnitude at 1, but the vector the same
				//Set Vector value of the ball to the Right side of the field
				dir = new Vector2(1, y).normalized;
			}else{
				//Set Vector value of the ball to the Left side of the field
				dir = new Vector2(-1, y).normalized;
			}
			// Set new velocity of the ball
			this.GetComponent<Rigidbody2D>().velocity = dir * speed;
			IncrementSpeed();
		}
		bounce.Play ();
	}

	void OnTriggerEnter2D(Collider2D col) {
		//If the ball has just passed into goal
		if (col.gameObject.tag == goal) {
			//If the goal in question is the LeftGoal, call the game managers rightscored procedure to increment Right's score value. Otherwise do the same for Left.
			if (col.gameObject.name == gLeft) {
				gameMS.RightScored ();
			} else {
				gameMS.LeftScored ();
			}
			//Destroy this ball object.
			Destroy (gameObject);
		} else {
			Destroy (gameObject);
			gameMS.OutOfBounds();
		}
	}

	float hitFactor(Vector2 ballPos, Vector2 racketPos, float racketHeight) {
		//Positive value means ball is above the mid-point of the racket, therefore send ball upwards
		//0 value means ball is at the centre of the racket, just return it with a y=0 vector
		//Negative value means ball is below the mid-point of the racket, therefore send ball downwards
		//
		//NOTE - This doesn't take into account the original position of the ball, i.e. it comes from above
		//			and hits above the mid point it'll be returned along that same route it came from. 
		//			This isn't how it would work obviously, it should just flip the X vector value & increase/decrease the Y vector value
		return (ballPos.y - racketPos.y) / racketHeight;
	}

	void IncrementSpeed() {
		speed++;
	}
}
