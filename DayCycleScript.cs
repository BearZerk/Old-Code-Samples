using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DayCycleScript : MonoBehaviour {

    private float timeOfDay = 0;
    private float cycleTime = 10;
    const int second = 1;
    const int minute = 60 * second;
    const int hour = 60 * minute;
    const int daynight = 12 * hour;
    private float sunRotation;
    private float degreeOverTime = 360 / daynight;
    private GameObject sunObject;

    private void Awake()
    {
        sunObject = GameObject.Find("Sun");
        if (sunObject == null) throw new System.ApplicationException("NO LIGHT AVAILABLE");
    }

	// Update is called once per frame
	void Update () {
        sunRotation = degreeOverTime * daynight / cycleTime * hour;
        sunObject.transform.Rotate(new Vector3(sunRotation, 0, 0) * Time.deltaTime);
        timeOfDay += Time.deltaTime;
    }

    int GetTimeHours()
    {
        return (int)(timeOfDay / hour);
    }

    int GetTimeMinutes()
    {
        return (int)(timeOfDay / minute);
    }

    int GetTimeSeconds()
    {
        return (int)(timeOfDay / second);
    }
}