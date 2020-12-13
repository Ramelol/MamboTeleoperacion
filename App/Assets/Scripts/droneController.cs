using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class droneController : MonoBehaviour
{
    private InstantTrackingController trackerScript;
    void Start(){
        trackerScript = GameObject.Find("Controller").gameObject.GetComponent<InstantTrackingController>();
        trackerScript._gridRenderer.enabled = false;
        trackerScript.ButtonDock.SetActive(false);
    }

    private void OnEnable()
    {
        trackerScript._gridRenderer.enabled = false;
        trackerScript.ButtonDock.SetActive(false);
    }

    public void OnDisable()
    {
        trackerScript.ButtonDock.SetActive(true);
    }
    void Update()
    {
        
    }
}
