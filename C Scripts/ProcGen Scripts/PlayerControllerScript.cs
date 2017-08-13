using UnityEngine;
using System.Collections;

//Player script
//Some focus on the Platformer lab given to us (labs 3 & 4) but with extended functionality such as Spike traps, Dying animation & seeing if falling
public class PlayerControllerScript : MonoBehaviour {

	public enum animationState
	{
		None,
		WalkLeft,
		WalkRight,
		StandLeft,
		StandRight,
		FallLeft,
		FallRight,
		DieRight,
		DieLeft
	}
	public enum facing
	{
		Right,
		Left
	}
	private bool running = false;
	private bool grounded = true;
	private bool canJump = true;

	private float tempy;
	private bool isFall = false;

	private int groundMask = 1 << 8; //Ground Layger Mask (User Layer 8)

	private facing currentFacing;
	private int animState = Animator.StringToHash("AnimState");
	private Animator animator;
	private animationState currentAnimation = animationState.None;

	private GameControllerScript gcs;

	public AudioClip jumpnoise;

	void Start()
	{
		GameObject gameControllerObject = GameObject.FindWithTag ("GameController");
		
		if(gameControllerObject != null)
		{
			gcs = gameControllerObject.GetComponent<GameControllerScript>();
		}
		if(gcs == null)
		{
			Debug.Log("Cannot find 'GameController' script");
		}

	}

	void Awake()
	{
		//get associated animator component
		animator = this.GetComponent<Animator> ();
	}
	
	void Update()
	{
		//run left
		if(running == true
		   && grounded == true
		   && currentFacing == facing.Left
		   && currentAnimation != animationState.WalkLeft)
		{
			currentAnimation = animationState.WalkLeft;
			animator.SetInteger(animState, 1);
			transform.localScale = new Vector3(-1,1,1);
		}

		//run right
		if(running == true
		   && grounded == true
		   && currentFacing == facing.Right
		   && currentAnimation != animationState.WalkRight)
		{
			currentAnimation = animationState.WalkRight;
			animator.SetInteger(animState, 1);
			transform.localScale = new Vector3(1,1,1);
		}

		//stand left
		if(running == false
		   && grounded == true
		   && currentFacing == facing.Left
		   && currentAnimation != animationState.StandLeft)
		{
			currentAnimation = animationState.StandLeft;
			animator.SetInteger(animState, 0);
			transform.localScale = new Vector3(-1,1,1);
		}

		//stand right
		if(running == false
		   && grounded == true
		   && currentFacing == facing.Right
		   && currentAnimation != animationState.StandRight)
		{
			currentAnimation = animationState.StandRight;
			animator.SetInteger(animState, 0);
			transform.localScale = new Vector3(1,1,1);
		}

		//fall left
		if(grounded == false
		   && currentFacing == facing.Left
		   && currentAnimation != animationState.FallLeft)
		{
			currentAnimation = animationState.FallLeft;
			animator.SetInteger(animState, 2);
			transform.localScale = new Vector3(-1,1,1);
		}

		//fall right
		if(grounded == false
		   && currentFacing == facing.Right
		   && currentAnimation != animationState.FallRight)
		{
			currentAnimation = animationState.FallRight;
			animator.SetInteger(animState, 2);
			transform.localScale = new Vector3(1,1,1);
		}
	}


	void FixedUpdate()
	{
		running = false;

		//New velocity to apply to player, Left & Right key handling
		Vector2 physicsVelocity = Vector2.zero;
		if(Input.GetKey (KeyCode.A))
		{
			currentFacing = facing.Left;
			physicsVelocity.x -= 2;
			running = true;
		}
		if(Input.GetKey (KeyCode.D))
		{
			currentFacing = facing.Right;
			physicsVelocity.x += 2;
			running = true;
		}

		//Allow player to jump if bool is true
		if(Input.GetKey (KeyCode.W))
		{
			if(canJump)
			{
				GetComponent<Rigidbody>().velocity = new Vector2(physicsVelocity.x, 6);
				canJump = false;
				grounded = false;
				AudioSource.PlayClipAtPoint(jumpnoise, transform.position);
			}
		}

		//Test to see if actually standing on ground, therefore if jump if again available
		if(Physics.Raycast
		   (new Vector2 (transform.position.x - 0.1f, transform.position.y), -Vector2.up, 0.35f, groundMask))
		{
			canJump = true;
			grounded = true;
			isFall = false;
		}
	
		else
		{
			if(tempy > transform.position.y)
			{
				isFall = true;
			}
			GetComponent<Rigidbody>().AddForce(-Vector2.up * 1f);
		}

		//Apply appropriate velocity to the body
		GetComponent<Rigidbody>().velocity = new Vector2 (physicsVelocity.x, GetComponent<Rigidbody>().velocity.y);
		tempy = transform.position.y;
	}

}
