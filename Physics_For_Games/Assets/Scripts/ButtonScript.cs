﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ButtonScript : MonoBehaviour
{
    // public variables
    public LayerMask TargetLayer;
    public GameObject DisplayPressE;
    public GameObject WreckingBall;
    public GameObject WallInvisableCollider;
    public RawImage Fader;

    // camera access to enable/disable
    public GameObject FPCamera;
    public GameObject CutSceneCamera;

    // used to freeze the player
    public GameObject FPPlayer;

    // Played == true once the cutscene is played (can only be played once per run time)
    private bool Played = false;

    private void Start()
    {
        // set gameobjects to active and disactive as needed
        FPCamera.SetActive(true);
        DisplayPressE.SetActive(false);
        CutSceneCamera.SetActive(false);
        WallInvisableCollider.SetActive(true);
    }

    void Update()
    {
        if (!Played)
        {
            // check if player is close enough to button
            Collider[] hitColliders = Physics.OverlapSphere(gameObject.transform.position, 0.5f, TargetLayer);
            int i = 0;

            // check to see if plaer is looking at the button
            RaycastHit hit;
            if (i < hitColliders.Length && Physics.Raycast(FPCamera.transform.position, FPCamera.transform.forward, out hit) && hit.transform.tag == "Button")
            {
                DisplayPressE.SetActive(true);
                if (Input.GetKey(KeyCode.E))
                {
                    // disable the player
                    FPPlayer.GetComponent<FPSMovement>().ableToMove = false;
                    FPCamera.GetComponent<FPSController>().ableToMove = false;

                    // deavtictivate invisable wall collider
                    WallInvisableCollider.SetActive(false);
                    Played = true;

                    // prepare to begin cutscene and call all functions
                    DisplayPressE.SetActive(false);
                    WreckingBall.GetComponent<Rigidbody>().isKinematic = false;
                    Fader.CrossFadeAlpha(1, 0.5f, true);
                    StartCoroutine("TriggerCutScene");
                }
            }
            else
            {
                // does not display "Press E" unless close enough and looking at button 
                DisplayPressE.SetActive(false);
            }
        }
        else
            DisplayPressE.SetActive(false);
    }

    // could be better but coroutines are confusing :/
    IEnumerator TriggerCutScene()
    {
        // face to cut scene camera
        yield return new WaitForSecondsRealtime(1);

        // swap activated camera to the cut scene camera
        FPCamera.SetActive(false);
        CutSceneCamera.SetActive(true);

        Fader.CrossFadeAlpha(0, 0.5f, true);
        yield return new WaitForSecondsRealtime(1);

        // wait time for cut scene
        yield return new WaitForSecondsRealtime(5);
        Fader.CrossFadeAlpha(1, 1, true);

        // fade back to first person camera
        yield return new WaitForSecondsRealtime(1);

        // swap activated camera to first person camera
        CutSceneCamera.SetActive(false);
        FPCamera.SetActive(true);
        FPPlayer.GetComponent<FPSMovement>().ableToMove = true;
        FPCamera.GetComponent<FPSController>().ableToMove = true;

        Fader.CrossFadeAlpha(0, 1, true);
        yield return new WaitForSecondsRealtime(1);

    }
}
