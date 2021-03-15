using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

// requires raw image on gui
public class FadeInOnStart : MonoBehaviour
{
    public RawImage Fader;

    void Start()
    {
        Fader.CrossFadeAlpha(0, 1, true);
    }
}
