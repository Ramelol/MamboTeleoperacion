using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class DownButton : MonoBehaviour, IPointerDownHandler
{
    public float dZ;
    public bool buttonPressed;
    public void updatePosition()
    {
        dZ -= 0.09f;
    }
    public void OnPointerDown(PointerEventData data)
    {
        buttonPressed = true;
    }
    public void OnDown()
    {
        buttonPressed = false;
        dZ = 0.0f;
    }
    void Start()
    {
        dZ = 0.0f;
    }
    void Update()
    {
        if (buttonPressed)
        {
            updatePosition();
        }
    }
}