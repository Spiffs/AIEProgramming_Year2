using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeInOnStartForThis : MonoBehaviour
{
    void Start()
    {
        GetComponent<RawImage>().CrossFadeAlpha(0, 1, true);
    }
}
