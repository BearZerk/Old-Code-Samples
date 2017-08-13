using UnityEngine;
using System.Collections;

public class GridScript : MonoBehaviour {

    //Defining the grid
    public static int w = 10;
    public static int h = 20;
    //Define as Transform, GameObject would work, but then each bit of code would say gameobjectvalue.transform.position
    public static Transform[,] grid = new Transform[w, h];

    //Rouding function to make sure the grid stays at proper integer values
    public static Vector2 roundVec2(Vector2 v)
    {
        return new Vector2(Mathf.Round(v.x), Mathf.Round(v.y));
    }

    //Function determines if within the borders. X needs to be between 0 & max-width value && y needs to be at least bigger than 0
    public static bool insideBorder(Vector2 pos)
    {
        return ((int)pos.x >= 0 && (int)pos.x < w && (int)pos.y >= 0);
    }

    //Function to delete a row of blocks
    public static void deleteRow(int y)
    {
        //for each value horizontally along the row
        for(int x = 0; x < w; x++)
        {
            //Destroy the gameObject there & then set a flag of empty
            Destroy(grid[x, y].gameObject);
            grid[x, y] = null;
        }
    }

    //Function to move rows down after a row is deleted
    public static void decreaseRow(int y)
    {
        //for every x value in a row
        for (int x = 0; x < w; x++)
        {
            //if it isn't empty
            if(grid[x,y] != null)
            {
                //set the value of 1 below to equal the value above, & set the above value to be null
                grid[x, y - 1] = grid[x, y];
                grid[x, y] = null;

                //Update the Blocks world position
                grid[x, y - 1].position += new Vector3(0, -1, 0);
            }
        }
    }

    //Function to move all rows above the deleted row down
    public static void decreaseRowsAbove(int y)
    {
        //for every row at current point to max height, bring it all down 1 row
        for (int i = y; i < h; i++)
            decreaseRow(i);
    }

    //Function to determine if a row is actually full
    public static bool isRowFull(int y)
    {
        //For every x value in a row
        for(int x=0; x < w; x++)
        {
            //If the current value is empty, return false
            if (grid[x, y] == null)
                return false;
        }
        //if we've not exited yet the row must be full
        return true;
    }

    //Function to delete a row, move the row down & all rows above too
    public static void deleteFullRows()
    {
        //For every height value from the bottom up
        for (int y = 0; y < h; y++)
        {
            //Check to see if it's a full row
            if(isRowFull(y))
            {
                //If it is, delete the row, move everything down and decrease the y value (this is because we just deleted and moved all rows down so y must be re-set to the index it should have remained at)
                deleteRow(y);
                decreaseRowsAbove(y + 1);
                y--;
            }
        }
    }
}
