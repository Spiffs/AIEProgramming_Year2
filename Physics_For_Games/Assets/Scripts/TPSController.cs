using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSController : MonoBehaviour
{
    private CharacterController controller;
    private Vector3 playerVelocity;
    private bool groundedPlayer;
    public bool ableToMove = true;
    private float playerSpeed = 2.85f;
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
        // checking if the character is grounded
        groundedPlayer = controller.isGrounded;
        if (groundedPlayer && playerVelocity.y < 0)
        {
            playerVelocity.y = 0f;
        }

        if (ableToMove)
        {
            // speed multiplier
            float speedMultiplier;
            if (Input.GetKey(KeyCode.LeftShift))
                speedMultiplier = 2.85f;
            else
                speedMultiplier = 1;

            // mouse position
            float MouseX = Input.GetAxis("Horizontal");
            float MouseY = Input.GetAxis("Vertical");

            // moving the Character 
            Vector3 move = transform.right * MouseX + transform.forward * MouseY;
            controller.Move(move * Time.deltaTime * playerSpeed * speedMultiplier);

            // setting the animator floats for animations, also accounts for sprinting
            animator.SetFloat("XPos", Mathf.Lerp(animator.GetFloat("XPos"), MouseX * speedMultiplier, 0.4f));
            animator.SetFloat("YPos", Mathf.Lerp(animator.GetFloat("YPos"), MouseY * speedMultiplier, 0.4f));

            // jumping functionality
            if (Input.GetButtonDown("Jump") && groundedPlayer)
            {
                playerVelocity.y += Mathf.Sqrt(jumpHeight * -3.0f * gravityValue);
            }
        }
        // adding gravity and moving the character controller accordingly
        playerVelocity.y += gravityValue * Time.deltaTime;
        controller.Move(playerVelocity * Time.deltaTime);
    }
}