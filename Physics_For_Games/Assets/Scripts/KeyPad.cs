using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class KeyPad : MonoBehaviour
{
    // password access and management
    private List<float> password = new List<float>();
    private List<float> passwordgoal = new List<float>();
    private bool solved = false;

    // decifering a player with its layer
    public LayerMask targetLayer;

    // barrier removal
    public GameObject barrier;

    // input text control
    public TextMeshProUGUI previewText;

    // player
    public GameObject player;

    public Canvas KeyPadCanvas;

    // Start is called before the first frame update
    void Start()
    {
        // make barrier active
        barrier.SetActive(true);

        // create the password goal or the set password
        passwordgoal.Add(1);
        passwordgoal.Add(2);
        passwordgoal.Add(3);
        passwordgoal.Add(4);

        // inavtivate all the UI
        KeyPadCanvas.gameObject.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if (!solved)
        {
            Collider[] hitColliders = Physics.OverlapSphere(gameObject.transform.position, 1f, targetLayer);

            if (hitColliders.Length > 0)
            {
                player.GetComponent<TPSController>().ableToMove = false;

                // if the player is in range then set all to true
                KeyPadCanvas.gameObject.SetActive(true);
            }

            // input any filler preview text
            if (password.Count == 1)
                previewText.text = "*";
            else if (password.Count == 2)
                previewText.text = "**";
            else if (password.Count == 3)
                previewText.text = "***";
            else if (password.Count == 4)
                previewText.text = "****";
            else
                previewText.text = "";

            // if the password is complete then check and if wrong then clear
            if (password.Count >= 4)
            {
                if (password[0] == passwordgoal[0] &&
                    password[1] == passwordgoal[1] &&
                    password[2] == passwordgoal[2] &&
                    password[3] == passwordgoal[3])
                    Solved();
                else
                    password.Clear();
            }
        }
    }

    private void Solved()
    {
        barrier.SetActive(false);
        solved = true;
        player.GetComponent<TPSController>().ableToMove = true;
        KeyPadCanvas.gameObject.SetActive(false);
    }

    // adding a float to all the buttons 
    public void OneButton()
    {
        password.Add(1);
    }

    public void TwoButton()
    {
        password.Add(2);
    }
    public void ThreeButton()
    {
        password.Add(3);
    }
    public void FourButton()
    {
        password.Add(4);
    }
    public void FiveButton()
    {
        password.Add(5);
    }
    public void SixButton()
    {
        password.Add(6);
    }
    public void SevenButton()
    {
        password.Add(7);
    }
    public void EightButton()
    {
        password.Add(8);
    }
    public void NineButton()
    {
        password.Add(9);
    }
}
