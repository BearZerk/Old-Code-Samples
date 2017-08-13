using UnityEngine;
using System.Collections;

public class GroupScript : MonoBehaviour {

    float lastFall = 0;

    bool isValidGridPos()
    {
        //for every single transform
        foreach (Transform child in transform)
        {
            //get the rounded vector value of the transform.
            Vector2 v = GridScript.roundVec2(child.position);

            //See if it's inside the border
            if (!GridScript.insideBorder(v))
                return false;

            //See if it's in a particular grid cell AND isn't part of the same group
            if (GridScript.grid[(int)v.x, (int)v.y] != null && GridScript.grid[(int)v.x, (int)v.y].parent != transform)
                return false;
        }
        return true;
    }

    void updateGrid()
    {
        //Remove old children from grid
        //For every y value, and for every x value in that y value (i.e. row by row from left to right)
        for (int y = 0; y < GridScript.h; y++)
            for (int x = 0; x < GridScript.w; x++)
                //If the value ISN'T empty
                if (GridScript.grid[x, y] != null)
                    //If the values parent is the current transform
                    if (GridScript.grid[x, y].parent == transform)
                        //Set the gridspace to empty
                        GridScript.grid[x, y] = null;

        //Add new children to grid
        foreach(Transform child in transform)
        {
            Vector2 v = GridScript.roundVec2(child.position);
            GridScript.grid[(int)v.x, (int)v.y] = child;
        }
    }

    void Update()
    {
        //Move left
        if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            //Modify position
            transform.position += new Vector3(-1, 0, 0);

            //See if this is valid
            if (isValidGridPos())
                //If so update the grid
                updateGrid();
            else
                //If it's not valid, revert
                transform.position += new Vector3(1, 0, 0);
        }
        //Move Right
        else if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            //Mod pos
            transform.position += new Vector3(1, 0, 0);

            //See if valid
            if (isValidGridPos())
                //Update grid
                updateGrid();
            else
                //Invalid? then revert
                transform.position += new Vector3(-1, 0, 0);
        }
        //Rotate
        else if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            transform.Rotate(0, 0, -90);

            //See if valid
            if (isValidGridPos())
                updateGrid();
            else
                transform.Rotate(0, 0, 90);
        }
        //Falling
        else if (Input.GetKeyDown(KeyCode.DownArrow) || Time.time - lastFall >= 1)
        {
            transform.position += new Vector3(0, -1, 0);

            if (isValidGridPos())
            {
                updateGrid();
            }
            else
            {
                transform.position += new Vector3(0, 1, 0);

                //Clear filled horizontal lines
                GridScript.deleteFullRows();

                //Spanw next group
                FindObjectOfType<SpawnScript>().spawnNext();

                //Disable script
                enabled = false;
            }

            lastFall = Time.time;
        }
    }

    void Start()
    {
        //Default position not valid? Then game over
        if(!isValidGridPos())
        {
            Debug.Log("GAME OVER");
            Destroy(gameObject);
        }
    }
}
