using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shoot : MonoBehaviour
{
    public GameObject Ball;
    Rigidbody rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Q))
        {
            GameObject newBall = Instantiate(Ball);
            newBall.transform.position = transform.position;
            newBall.GetComponent<Rigidbody>().AddForce(new Vector3(0, 0, -60), ForceMode.Impulse);
            newBall.GetComponent<Rigidbody>().useGravity = true;
        }
        if (Input.GetKeyDown(KeyCode.E))
        {
            GameObject newBall = Instantiate(Ball);
            newBall.transform.position = transform.position;
            newBall.GetComponent<Rigidbody>().AddForce(new Vector3(0, 0, 60), ForceMode.Impulse);
            newBall.GetComponent<Rigidbody>().useGravity = true;
        }
    }
}
