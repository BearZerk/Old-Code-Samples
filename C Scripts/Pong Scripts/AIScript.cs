using UnityEngine;
using System.Collections;

public class AIScript : MonoBehaviour {

	//Create a magnitude for the paddles velocity later
	public float speed = 5.0f;
	//Create a ball object to follow the height value of
	public GameObject ball;
	//Create a paddleheight variable to allow for simple calculations laterS
	private float aiHeight;
	//Set up a temporary RacketDistance value to keep the FixedUpdate solution more simple.
	private float tempRacketDist;
	//Set private bool to determine previous racket direction
	private bool velup;

	//Called on Instantiation of the AI Racket
	void Start() {
		aiHeight = GetComponent<Renderer> ().bounds.size.y;
	}

	void FixedUpdate() {
		//IF the ball is travelling TOWARD the AI Racket
		if (ball.GetComponent<Rigidbody2D> ().velocity.x > 0) {
			//Find out the Racket Distance Value
			RacketDistance();
			//If it's positive
			if(tempRacketDist > (0.5f*aiHeight)) {

				GetComponent<Rigidbody2D>().velocity = Vector2.up * speed;
				velup = true;

			//Otherwise it's in the negative direction
			} else if (tempRacketDist < (-0.5f*aiHeight) ) {

				GetComponent<Rigidbody2D>().velocity = Vector2.down * speed;
				velup = false;

			//If the ball is in the centre of the racket
			} else if ( tempRacketDist == 0 || tempRacketDist < (0.5f*aiHeight) && tempRacketDist > (-0.5f*aiHeight) ) {
				//If last direction was up
				if(velup) {
					//Continue up but have 1/3 speed
					GetComponent<Rigidbody2D>().velocity = Vector2.up * (0.25f * speed);
				//If last direction was down
				}else{ 
					//Continue down but at 1/3 speed
					GetComponent<Rigidbody2D>().velocity = Vector2.down * (0.25f * speed);
				}
				//GetComponent<Rigidbody2D>().velocity = Vector2 * (1/5*speed);

			}
		} else {
			//IF the ball isn't travelling TOWARD the AI Racket, set it's velocity to zero
			this.GetComponent<Rigidbody2D>().velocity = Vector2.zero;
		}
	}

	void RacketDistance() {
		//Positive value means ball is above the mid-point of the racket
		//0 value means ball is at the centre of the racket, just return it with a y=0 vector
		//Negative value means ball is below the mid-point of the racket
		//
		//NOTE - This is a repurposed rip-off of the HitFactor function in the BallScript.cs file
		tempRacketDist = (ball.transform.position.y - this.transform.position.y); 
	}
}
