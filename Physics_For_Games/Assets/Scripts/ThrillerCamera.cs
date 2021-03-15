using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThrillerCamera : MonoBehaviour
{
    public GameObject ThrillerDancer;

    // Update is called once per frame
    void Update()
    {
        transform.position = ThrillerDancer.transform.position;
        transform.RotateAround(ThrillerDancer.transform.position, Vector3.up, .4f);
    }
}
