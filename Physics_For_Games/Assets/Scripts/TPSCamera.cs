using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSCamera : MonoBehaviour
{
    public GameObject Target;
    public Vector3 Offset;
    public float MouseSensitivity;

    private float distance = 4f;
    private float currentY = 30f;
    private float currentX = 0f;

    public float clampMin = -30, clampMax = 60;

    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }

    void FixedUpdate()
    {
        // get the mouse axis
        currentX += Input.GetAxis("Mouse X") * MouseSensitivity * Time.deltaTime;
        currentY += Input.GetAxis("Mouse Y") * MouseSensitivity * Time.deltaTime;

        currentY = Mathf.Clamp(currentY, clampMin, clampMax);


        Vector3 dir = new Vector3(Offset.x, Offset.y, -distance);
        Quaternion rotation = Quaternion.Euler(currentY, 0, 0);
        transform.position = Target.transform.position + rotation * dir;
        transform.LookAt(Target.transform.position/* + Offset*/);

    }
}
