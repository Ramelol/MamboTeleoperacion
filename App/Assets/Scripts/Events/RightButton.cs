using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class RightButton : MonoBehaviour, IPointerDownHandler
{
    public float dY;
    public bool buttonPressed;
    public void updateY()
    {
        dY += 0.09f;
    }
    public void OnPointerDown(PointerEventData data)
    {
        buttonPressed = true;
    }
    public void OnUp()
    {
        buttonPressed = false;
        dY = 0.0f;
    }
    void Start()
    {
        dY = 0.0f;
    }
    void Update()
    {
        if (buttonPressed)
        {
            updateY();
        }
    }
}
