using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Raycast : MonoBehaviour
{
    public Text output;

    void Update()
    {
        Ray ray = UnityEngine.Camera.main.ScreenPointToRay(Input.mousePosition);

        RaycastHit hitInfo;
        if (Physics.Raycast(ray, out hitInfo, 500) == true)
        {
            output.text = hitInfo.transform.gameObject.name;
        }
    }
}
