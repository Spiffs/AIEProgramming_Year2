using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSCamera : MonoBehaviour
{
    public GameObject Target;
    public Vector3 OffSet;
    public float MouseSensitivity;

    private float XRotation = 0f;

    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        transform.position = Target.transform.position + OffSet;
    }

    void FixedUpdate()
    {
        // get the mouse axis
        float mouseX = Input.GetAxis("Mouse X") * MouseSensitivity * Time.deltaTime;
        float mouseY = Input.GetAxis("Mouse Y") * MouseSensitivity * Time.deltaTime;

        XRotation += mouseY;

        // look at the character
        transform.LookAt(Target.transform.position);

        // rotate the character around up 
        Target.transform.Rotate(Target.transform.up, mouseX);
        transform.RotateAround(Target.transform.position, Target.transform.right, mouseY);

    }
}
