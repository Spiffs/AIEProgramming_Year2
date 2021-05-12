using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Cinemachine;

public class EndSequence : MonoBehaviour
{
    // triggers
    public Collider DialogueTrigger1;
    public Collider DialogueTrigger2;
    public Collider DialogueTrigger3;
    public Collider DanceTrigger;

    // text
    public GameObject DialogueText1;
    public GameObject DialogueText2;
    public GameObject DialogueText3;
    public GameObject PressE;

    // player
    public GameObject TPPlayer;

    // cameras
    public CinemachineFreeLook TPCamera;
    public CinemachineVirtualCamera ThrillerCamera;

    // animator
    public GameObject Dancer;
    public GameObject Lights;

    // directional light
    public GameObject DirectionalLight;

    // black fader
    public RawImage Fader;

    // complete tracking
    private bool Dialogue1Complete = false, 
                 Dialogue2Complete = false, 
                 Dialogue3Complete = false,
                 DanceTriggered = false,
                 paused = false;

    // for rotationg directional light
    Quaternion targetRotation;

    // Start is called before the first frame update
    void Start()
    {
        // disable dialogue on run time
        DialogueText1.SetActive(false);
        DialogueText2.SetActive(false);
        DialogueText3.SetActive(false);
        PressE.SetActive(false);

        // disable secondary camera on runtime
        ThrillerCamera.m_Priority = 0;

        // directional light starting angle
        targetRotation = DirectionalLight.transform.rotation;
    }

    // Update is called once per frame
    void Update()
    {
        // lerp to rotate directional light
        DirectionalLight.transform.rotation = Quaternion.Lerp(DirectionalLight.transform.rotation, targetRotation, Time.deltaTime * 1);
        DirectionalLight.GetComponent<Light>().intensity = 1.2f - DirectionalLight.transform.rotation.eulerAngles.x / 180f;

        if (!Dialogue1Complete)
        {
            if (DialogueTrigger1.GetComponent<PlayerInTrigger>().playerEntered == true)
            {
                // modify bool to stop repeating code
                Dialogue1Complete = true;

                //set pause bool to true
                paused = true;

                //turn to night slowly
                Vector3 direction = new Vector3(-13, DirectionalLight.transform.rotation.eulerAngles.y, DirectionalLight.transform.rotation.eulerAngles.z);
                targetRotation = Quaternion.Euler(direction);

                

                // enable text
                DialogueText1.SetActive(true);
                PressE.SetActive(true);

                // disable player movement
                TPPlayer.GetComponent<TPSController>().ableToMove = false;
            }
        }
        else if (!Dialogue2Complete)
        {
            if (DialogueTrigger2.GetComponent<PlayerInTrigger>().playerEntered == true)
            {
                // modify bool to stop repeating code
                Dialogue2Complete = true;

                //set pause bool to true
                paused = true;

                // enable text
                DialogueText2.SetActive(true);
                PressE.SetActive(true);

                // disable player movement
                TPPlayer.GetComponent<TPSController>().ableToMove = false;
            }
        }
        else if (!Dialogue3Complete)
        {
            if (DialogueTrigger3.GetComponent<PlayerInTrigger>().playerEntered == true)
            {
                // modify bool to stop repeating code
                Dialogue3Complete = true;

                //set pause bool to true
                paused = true;

                // enable text
                DialogueText3.SetActive(true);
                PressE.SetActive(true);

                // disable player movement
                TPPlayer.GetComponent<TPSController>().ableToMove = false;
            }
        }
        else if (!DanceTriggered)
        {
            if (DanceTrigger.GetComponent<DanceTrigger>().playerEntered == true)
            {
                DanceTriggered = true;

                // play thriller :)
                GetComponent<AudioSource>().Play(0);

                // fade to black
                Fader.CrossFadeAlpha(1, 1, true);

                // begin coroutine for camera sawp
                Invoke("SwitchToThrillerCamera", 1);
                Lights.GetComponent<Lights>().StartLights = true;

                //set pause bool to true
                paused = true;

                // disable player movement
                TPPlayer.GetComponent<TPSController>().ableToMove = false;
            }
        }

        // unpausing
        if (paused)
        {
            if (Input.GetKey(KeyCode.E))
            {
                // disable all text
                DialogueText1.SetActive(false);
                DialogueText2.SetActive(false);
                DialogueText3.SetActive(false);
                PressE.SetActive(false);

                // enable player movement
                TPPlayer.GetComponent<TPSController>().ableToMove = true;
            }
        }

        // game exit on ESC 
        if (Input.GetKey(KeyCode.Escape))
        {
            Application.Quit();
        }
    }

    void SwitchToThrillerCamera()
    {
        TPCamera.m_Priority = 0;
        ThrillerCamera.Priority = 10;

        Fader.CrossFadeAlpha(0, 1, true);

        Dancer.GetComponent<Animator>().SetBool("BeginDance", true);
    }
}
