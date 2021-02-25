using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[CreateAssetMenu]
public class FPSCamera : MonoBehaviour
{
    public GameObject target;
    Vector3 offSet;

	[SerializeField]
	[Range(1, 1000)] public float MouseSensitivity;

    void FixedUpdate()
    {
        transform.position = target.transform.position + offSet;
        Vector3 targetrotation = target.transform.rotation.eulerAngles;
        float rotateHorizontal = Input.GetAxis("Mouse Y");
        transform.RotateAround(transform.position, transform.right, rotateHorizontal * MouseSensitivity * Time.fixedDeltaTime);
    }
}