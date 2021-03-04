using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shooting : MonoBehaviour
{
    public GameObject FPSCamObject;
    private Camera fpsCamera;

    private void Start()
    {
        fpsCamera = FPSCamObject.GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Fire1"))
        {
            Shoot();
        }
    }
    void Shoot()
    {
        RaycastHit hit;
        if (Physics.Raycast(fpsCamera.transform.position, fpsCamera.transform.forward, out hit))
        {
            Debug.Log(hit.transform.name + "Hit but no ragdoll");
            Ragdoll r = hit.transform.gameObject.GetComponent<Ragdoll>();
            if (r != null)
            {
                Debug.Log(hit.transform.name);
                r.RagdollOn = true;
            }
        }
    }

}
