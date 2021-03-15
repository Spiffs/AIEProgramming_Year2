using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DanceTrigger : MonoBehaviour
{
    public bool playerEntered = false;

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
            playerEntered = true;
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
            playerEntered = false;
    }
}
