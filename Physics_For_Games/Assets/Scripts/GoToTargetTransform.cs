using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoToTargetTransform : MonoBehaviour
{
    public GameObject Target;

    // Update is called once per frame
    void FixedUpdate()
    {
        transform.position = Target.transform.position;
        transform.rotation = Target.transform.rotation;
    }
}
