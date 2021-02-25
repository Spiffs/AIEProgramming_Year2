using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class FPSController : MonoBehaviour
{
    [SerializeField]
    [Range(1, 1000)] float MouseSensitivity;

    public float speed;
    CharacterController controller;

    // Start is called before the first frame update
    void Start()
    {
        controller = GetComponent<CharacterController>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        float vertical = Input.GetAxis("Vertical");
        float horizontal = Input.GetAxis("Horizontal");

        controller.SimpleMove(transform.forward * vertical * speed * Time.fixedDeltaTime);
        controller.SimpleMove(transform.right * horizontal * speed * Time.fixedDeltaTime);
        controller.SimpleMove(transform.up * Time.deltaTime);

        float rotateHorizontal = Input.GetAxis("Mouse X");
        transform.Rotate(transform.up * rotateHorizontal * MouseSensitivity * Time.fixedDeltaTime);
    }
}
