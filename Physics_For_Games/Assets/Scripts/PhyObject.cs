using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PhyObject : MonoBehaviour
{
    public Material awakeMat = null;
    public Material sleepingMat = null;

    private Rigidbody rb = null;

    private bool wasAsleep = false;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {
        if (rb.IsSleeping() && !wasAsleep && sleepingMat != null)
        {
            wasAsleep = true;
            GetComponent<MeshRenderer>().material = sleepingMat;
        }
        if(!rb.IsSleeping() && wasAsleep && awakeMat != null)
        {
            GetComponent<MeshRenderer>().material = awakeMat;
        }
    }
}
