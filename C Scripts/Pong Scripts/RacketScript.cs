using UnityEngine;
using System.Collections;


public class RacketScript : MonoBehaviour {

	//Create a magnitude for the paddles velocity later
	public float speed = 7.5f;
	//Create string value for which axis controls the Racket movement
	public string axis = "Vertical";

	//FixedUpdate used for changes to Rigidbody force values. 
	//Called every fixed frame, not every frame.
	void FixedUpdate () {
		float vert = Input.GetAxisRaw (axis);
		GetComponent<Rigidbody2D> ().velocity = new Vector2 (0, vert) * speed;
	}
}
