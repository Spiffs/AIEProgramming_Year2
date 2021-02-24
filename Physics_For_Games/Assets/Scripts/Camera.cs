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
            transform.Rotate(Vector3.up * 50 * Time.deltaTime);
        }
        if (Input.GetKey(KeyCode.J))
        {
            transform.Rotate(Vector3.up * -50 * Time.deltaTime);
        }
    }

}
