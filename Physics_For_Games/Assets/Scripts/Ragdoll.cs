using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Animator))]

public class Ragdoll : MonoBehaviour
{
    private Animator animator = null;
    public List<Rigidbody> rigidbodies = new List<Rigidbody>();

    public bool RagdollOn
    {
        get { return !animator.enabled; }
        set
        {
            GetComponent<CapsuleCollider>().isTrigger = true;
            animator.enabled = !value;
            foreach(Rigidbody r in rigidbodies)
            {
                r.isKinematic = !value;
            }
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        GetComponent<CapsuleCollider>().isTrigger = false;
        animator = GetComponent<Animator>();
        foreach(Rigidbody r in rigidbodies)
        {
            r.isKinematic = true;
        }
    }
}
