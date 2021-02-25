using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera : MonoBehaviour
{
    public GameObject target;
    public Vector3 offset;

    void FixedUpdate()
    {
        transform.position = target.transform.position + offset;
        
        if (Input.GetKey(KeyCode.K))
        {
            transform.RotateAround(target.transform.position, transform.up, 5 * Time.fixedDeltaTime);
        }
        if (Input.GetKey(KeyCode.J))
        {
            transform.RotateAround(target.transform.position, -transform.up, 5 * Time.fixedDeltaTime);
        }
    }

}
