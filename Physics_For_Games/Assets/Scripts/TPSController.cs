using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TPSController : MonoBehaviour
{
    public Transform tpc;

    private CharacterController controller;
    private Vector3 playerVelocity;
    private Animator animator;

    private bool groundedPlayer;
    public bool ableToMove = true;

    public float turnSmoothTime;
    float turnSmoothVelocity;
    private float playerSpeed = 2.85f;
    private float jumpHeight = 1.0f;
    private float gravityValue = -9.81f;

    public Material RegularMaterial1;
    public Material RegularMaterial2;
    public Material GlassMaterial;
    public Material GreenPattern;
    public Material RenderMaterial;

    public GameObject CharacterMesh;

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
            Vector3 direction = new Vector3(MouseX, 0, MouseY).normalized;

            if (direction.magnitude >= 0.1f)
            {
                float targetAngle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg + tpc.eulerAngles.y;
                float angle = Mathf.SmoothDampAngle(transform.eulerAngles.y, tpc.eulerAngles.y, ref turnSmoothVelocity, turnSmoothTime);
                transform.rotation = Quaternion.Euler(0f, angle, 0f);

                Vector3 moveDir = Quaternion.Euler(0f, targetAngle, 0f) * Vector3.forward;
                controller.Move(moveDir * playerSpeed * speedMultiplier * Time.deltaTime);
            }

            // setting the animator floats for animations, also accounts for sprinting
            animator.SetFloat("XPos", Mathf.Lerp(animator.GetFloat("XPos"), MouseX * speedMultiplier, 0.4f));
            animator.SetFloat("YPos", Mathf.Lerp(animator.GetFloat("YPos"), MouseY * speedMultiplier, 0.4f));

            // jumping functionality
            if (Input.GetButtonDown("Jump") && groundedPlayer)
            {
                playerVelocity.y += Mathf.Sqrt(jumpHeight * -3.0f * gravityValue);
            }
        }
        else
        {
            // mouse position
            float MouseX = 0;
            float MouseY = 0;
            
            animator.SetFloat("XPos", Mathf.Lerp(animator.GetFloat("XPos"), MouseX, 0.4f));
            animator.SetFloat("YPos", Mathf.Lerp(animator.GetFloat("YPos"), MouseY, 0.4f));
        }

        // adding gravity and moving the character controller accordingly
        playerVelocity.y += gravityValue * Time.deltaTime;
        controller.Move(playerVelocity * Time.deltaTime);
    }

    // swap to regular shader
    public void Material1()
    {
        Material[] newmats = CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials;
        newmats[0] = RegularMaterial2;
        newmats[1] = RegularMaterial1;
        CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials = newmats;
    }

    // sawp to glass shader
    public void Material2()
    {
        Material[] newmats = CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials;
        newmats[0] = GlassMaterial;
        newmats[1] = GlassMaterial;
        CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials = newmats;
    }

    // sawp to green cartoon chader
    public void Material3()
    {
        Material[] newmats = CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials;
        newmats[0] = GreenPattern;
        newmats[1] = GreenPattern;
        CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials = newmats;
    }
    public void Material4()
    {
        Material[] newmats = CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials;
        newmats[0] = RenderMaterial;
        newmats[1] = RenderMaterial;
        CharacterMesh.GetComponent<SkinnedMeshRenderer>().materials = newmats;
    }
}