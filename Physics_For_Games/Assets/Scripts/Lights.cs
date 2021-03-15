using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lights : MonoBehaviour
{
    public GameObject BlueLight;
    public GameObject RedLight;
    public GameObject GreenLight;
    public GameObject YellowLight;

    public bool StartLights = false;

    // Start is called before the first frame update
    void Start()
    {
        BlueLight.SetActive(false);
        RedLight.SetActive(false);
        GreenLight.SetActive(false);
        YellowLight.SetActive(false);

        
    }

    private void Update()
    {
        if (StartLights)
        {
            StartLights = false;
            StartCoroutine("LightShow");
        }

    }

    IEnumerator LightShow()
    {
        YellowLight.SetActive(false);
        BlueLight.SetActive(true);

        yield return new WaitForSeconds(0.25f);

        BlueLight.SetActive(false);
        RedLight.SetActive(true);

        yield return new WaitForSeconds(0.25f);
        
        RedLight.SetActive(false);
        GreenLight.SetActive(true);

        yield return new WaitForSeconds(0.25f);

        GreenLight.SetActive(false);
        YellowLight.SetActive(true);

        yield return new WaitForSeconds(0.25f);

        StartCoroutine("LightShow");
    }
}
