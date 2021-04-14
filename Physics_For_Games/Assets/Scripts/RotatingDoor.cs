using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RotatingDoor : MonoBehaviour
{
    public float angleZ = 0;
    void FixedUpdate()
    {
        angleZ = transform.localRotation.eulerAngles.z;
        if (angleZ <= 285 && angleZ >= 200)
        {
            GetComponent<Rigidbody>().isKinematic = true;
        }
    }
}
