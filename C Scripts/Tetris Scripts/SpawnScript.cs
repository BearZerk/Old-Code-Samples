using UnityEngine;
using System.Collections;

public class SpawnScript : MonoBehaviour {

    //Array filled with Letter-Groups (I,O,L,J,S,Z,T), assigned values in Inspector
    public GameObject[] groups;

    public void spawnNext()
    {
        //Creating psuedo-random value to generate which shape to instantiate later
        int i = Random.Range(0, groups.Length);

        //Instantiate object at current position (position of Spawner Object & default rotation)
        Instantiate(groups[i], transform.position, Quaternion.identity);
    }

    //Called at start of the scene after everything is loaded.
    void Start()
    {
        //Spawn initial item
        spawnNext();
    }
}
