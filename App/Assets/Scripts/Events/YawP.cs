using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;


public class YawP : MonoBehaviour, IPointerDownHandler
{
    public float dYaw;
    public bool buttonPressed;
    public void updateYaw()
    {
        dYaw += 0.09f;
    }
    public void OnPointerDown(PointerEventData data)
    {
        buttonPressed = true;
    }
    public void OnUp()
    {
        buttonPressed = false;
        dYaw = 0.0f;
    }
    void Start()
    {
        dYaw = 0.0f;
    }
    void Update()
    {
        if (buttonPressed)
        {
            updateYaw();
        }
    }
}
