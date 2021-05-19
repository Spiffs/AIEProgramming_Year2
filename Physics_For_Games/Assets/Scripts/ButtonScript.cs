using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Cinemachine;

public class ButtonScript : MonoBehaviour
{
    // public variables
    public LayerMask TargetLayer;

    // ui Button
    public GameObject ButtonUp;
    public GameObject ButtonDown;
    private bool ButtonButtonOrSomething = false;
    private bool ButtonPushed = false;

    public GameObject WreckingBall;
    public GameObject WallInvisableCollider;
    public RawImage Fader;

    // camera access to enable/disable
    public CinemachineFreeLook ThirdPersonCamera;
    public CinemachineVirtualCamera CutSceneCamera;

    private float SelectedCamera = 0;

    // Played == true once the cutscene is played (can only be played once per run time)
    private bool Played = false;

    private void Start()
    {
        ThirdPersonCamera.m_Priority = 10;
        CutSceneCamera.m_Priority = 1;

        // set gameobjects to active and disactive as needed
        ButtonUp.SetActive(false);
        ButtonDown.SetActive(false);
        WallInvisableCollider.SetActive(true);
    }

    void Update()
    {
        // make sure both buttons are already disapeared 
        ButtonUp.SetActive(false); ButtonDown.SetActive(false);

        SwitchCamera();

        if (!Played)
        {
            // check if player is close enough to button
            Collider[] hitColliders = Physics.OverlapSphere(gameObject.transform.position, 1f, TargetLayer);
            int i = 0;

            if (i < hitColliders.Length)
            {
                if (ButtonPushed)
                {
                    ButtonUp.SetActive(false);
                    ButtonDown.SetActive(true);
                    if (ButtonButtonOrSomething)
                    {
                        WallInvisableCollider.SetActive(false);
                        Played = true;

                        WreckingBall.GetComponent<Rigidbody>().isKinematic = false;

                        Fader.CrossFadeAlpha(1, 1, true);
                        StartCoroutine("TriggerCutScene");
                    }
                }
                else
                {
                    ButtonUp.SetActive(true);
                    ButtonDown.SetActive(false);
                }

                // display the button correctly on mouse down or up
                if (Input.GetMouseButtonUp(0))
                    ButtonPushed = false;

                else if (Input.GetMouseButtonDown(0))
                    ButtonPushed = true;
            }
        }
    }

    void SwitchCamera()
    {
        if (SelectedCamera == 1)
        {
            ThirdPersonCamera.m_Priority = 2;
            CutSceneCamera.m_Priority = 1;
        }
        else if (SelectedCamera == 2)
        {
            ThirdPersonCamera.m_Priority = 1;
            CutSceneCamera.m_Priority = 2;
        }
    }

    // could be better but coroutines are confusing :/
    IEnumerator TriggerCutScene()
    {
        // face to cut scene camera
        yield return new WaitForSecondsRealtime(1);

        // swap activated camera to the cut scene camera
        SelectedCamera = 2;

        Fader.CrossFadeAlpha(0, 0.5f, true);
        yield return new WaitForSecondsRealtime(1);

        // wait time for cut scene
        yield return new WaitForSecondsRealtime(5);
        Fader.CrossFadeAlpha(1, 1, true);

        // fade back to first person camera
        yield return new WaitForSecondsRealtime(1);

        // swap activated camera to first person camera
        SelectedCamera = 1;

        Fader.CrossFadeAlpha(0, 1, true);
        yield return new WaitForSecondsRealtime(1);

    }

    public void OnButtonButton()
    {
        ButtonButtonOrSomething = true;
    }
}
