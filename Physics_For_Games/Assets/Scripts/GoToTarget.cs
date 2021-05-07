using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoToTarget : MonoBehaviour
{
    public GameObject Target;

    public Vector3 Offset;

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = Target.transform.position + Offset;
        transform.rotation = new Quaternion(0, 0, 0, 0);
    }
}
