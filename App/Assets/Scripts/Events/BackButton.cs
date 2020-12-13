using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;


public class BackButton : MonoBehaviour, IPointerDownHandler
{
    public float dX;
    public bool buttonPressed;
    public void updateX()
    {
        dX -= 0.09f;
    }
    public void OnPointerDown(PointerEventData data)
    {
        buttonPressed = true;
    }
    public void OnUp()
    {
        buttonPressed = false;
        dX = 0.0f;
    }
    void Start()
    {
        dX = 0.0f;
    }
    void Update()
    {
        if (buttonPressed)
        {
            updateX();
        }
    }
}