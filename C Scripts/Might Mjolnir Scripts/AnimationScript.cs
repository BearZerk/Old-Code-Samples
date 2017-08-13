using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AnimationScript : MonoBehaviour {

    //Setup private Animation component for the player
    private Animator playerAnim;
    //Setup parameter variable for AnimationTree
    private int MousePressVal;
    //Setup private enum to help transition Animation states
    enum PlayerAnimationState
    {
        idle,
        firstswing,
        secondswing,
        slam,
        firstthrow,
        secondthrow,
    };
    //Private enum Variable
    PlayerAnimationState pas;
    //Set up queue for linking back to Idle
    private Queue<int> attackQueue = new Queue<int>();
    //private values for keeping an active combo queu
    private float comboTimeWindow;
   
	// Use this for initialization
	void Start () {
        //Set private Animation component to the Animation component attached to this item
        playerAnim = GetComponent<Animator>();
        pas = PlayerAnimationState.idle;
        comboTimeWindow = 1f;
    }
	
	// Update is called once per frame
	void Update () {
        //=============================================Handling Input=============================================//
        if (Input.GetMouseButtonUp(0))
        {
            //Left Mouse Press
            MousePressVal = 0;
            PlayAnimationTree(MousePressVal);
        }else if (Input.GetMouseButtonUp(1))
        {
            //Right Mouse Press
            MousePressVal = 1;
            PlayAnimationTree(MousePressVal);
        }

        if(comboTimeWindow > 0)
            comboTimeWindow -= Time.deltaTime;
    }

    void FixedUpdate()
    {
        if(attackQueue.Count > 0)
        {
            playerAnim.SetInteger("EnumPAS", attackQueue.Peek());
            attackQueue.Dequeue();
        }
        //=============================================Combo Queue Handle=============================================//
        if (comboTimeWindow == 0 || comboTimeWindow < 0)
        {
            attackQueue.Clear();
            pas = PlayerAnimationState.idle;
            playerAnim.SetInteger("EnumPAS", (int)pas);
        }
    }

    void PlayAnimationTree(int MouseAttackVal)
    {
        switch(MouseAttackVal)
        {
            case 0:
                if(pas == PlayerAnimationState.idle)
                {
                    pas = PlayerAnimationState.firstswing;
                    comboTimeWindow += 1f;
                }
                else if(pas == PlayerAnimationState.firstswing)
                {
                    pas = PlayerAnimationState.secondswing;
                    comboTimeWindow += 1f;
                }
                else if(pas == PlayerAnimationState.secondswing)
                {
                    pas = PlayerAnimationState.slam;
                }
                break;
            case 1:
                if(pas == PlayerAnimationState.idle)
                {
                    pas = PlayerAnimationState.firstthrow;
                    comboTimeWindow += 1f;
                }
                else if(pas == PlayerAnimationState.firstswing)
                {
                    pas = PlayerAnimationState.secondthrow;
                }
                break;
            default:
                return;
        }
        attackQueue.Enqueue((int)pas);
    }
}
