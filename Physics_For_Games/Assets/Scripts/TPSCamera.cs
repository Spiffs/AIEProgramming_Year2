using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSCamera : MonoBehaviour
{
    public GameObject Target;
    public Vector3 OffSet;

    public float MouseSensitivity;

    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
        transform.position = Target.transform.position + OffSet;
    }

    void FixedUpdate()
    {
        //transform.position = Target;

        float mouseX = Input.GetAxis("Mouse X") * MouseSensitivity * Time.deltaTime;
        float mouseY = Input.GetAxis("Mouse Y") * MouseSensitivity * Time.deltaTime;

        transform.LookAt(Target.transform.position);

        Target.transform.Rotate(Target.transform.up, mouseX);
        transform.RotateAround(Target.transform.position, Target.transform.right, mouseY);

    }
}
