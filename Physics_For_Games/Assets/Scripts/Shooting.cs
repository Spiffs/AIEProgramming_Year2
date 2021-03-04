using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shooting : MonoBehaviour
{
    public Camera fpsCamera;
    public ParticleSystem muzzleFlash;

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
            if (muzzleFlash != null)
                muzzleFlash.Play();

            Debug.Log(hit.transform.name + "Hit but no ragdoll");
            Ragdoll r = hit.transform.gameObject.GetComponent<Ragdoll>();
            Rigidbody hitRB = hit.transform.GetComponent<Rigidbody>();

            if (r != null && r.RagdollOn == false)
                r.RagdollOn = true;
            else if (hitRB != null)
            {
                hitRB.AddForceAtPosition(-hit.normal * 50, hit.point, ForceMode.Impulse);
            }
        }
    }

}
