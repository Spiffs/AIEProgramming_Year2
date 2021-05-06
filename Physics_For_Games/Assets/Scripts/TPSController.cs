using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSController : MonoBehaviour
{
    private CharacterController controller;
    private Vector3 playerVelocity;
    private bool groundedPlayer;
    private float playerSpeed = 1.75f;
    private float jumpHeight = 1.0f;
    private float gravityValue = -9.81f;
    private Animator animator;

    private void Start()
    {
        animator = GetComponent<Animator>();
        controller = GetComponent<CharacterController>();
    }

    void Update()
    {
        groundedPlayer = controller.isGrounded;
        if (groundedPlayer && playerVelocity.y < 0)
        {
            playerVelocity.y = 0f;
        }

        float speedMultiplier;
        if (Input.GetKey(KeyCode.LeftShift))
            speedMultiplier = 2.85f;
        else
            speedMultiplier = 1;

        float MouseX = Input.GetAxis("Horizontal");
        float MouseY = Input.GetAxis("Vertical");

        Vector3 move = transform.right * MouseX + transform.forward * MouseY;
        controller.Move(move * Time.deltaTime * playerSpeed * speedMultiplier);

        animator.SetFloat("XPos", Mathf.Lerp(animator.GetFloat("XPos"), MouseX * speedMultiplier, 0.4f));
        animator.SetFloat("YPos", Mathf.Lerp(animator.GetFloat("YPos"), MouseY * speedMultiplier, 0.4f));

        // Changes the height position of the player..
        if (Input.GetButtonDown("Jump") && groundedPlayer)
        {
            playerVelocity.y += Mathf.Sqrt(jumpHeight * -3.0f * gravityValue);
        }  

        playerVelocity.y += gravityValue * Time.deltaTime;
        controller.Move(playerVelocity * Time.deltaTime);
    }
}