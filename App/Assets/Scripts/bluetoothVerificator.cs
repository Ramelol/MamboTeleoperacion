using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class bluetoothVerificator : MonoBehaviour
{
    public GameObject warningPanel;
    public GameObject mainPanel;
    private float timer;
    private bool timerActive;

    public void updateTimer()
    {
        if (timerActive)
        {
            timer -= Time.deltaTime;
        }
        if (Mathf.Abs(timer) < 0.1)
        {
            warningPanel.SetActive(false);
            timerActive = false;
            mainPanel.SetActive(true);
            timer = 12.0f;
            SceneManager.LoadScene("Main");
        }
    }

    public void verifyBtConnection()
    {
        string[] connectedJoystick = Input.GetJoystickNames();
        if (connectedJoystick.Length == 0 || connectedJoystick[0] == "")
        {
            warningPanel.SetActive(true);
            mainPanel.SetActive(false);
            timerActive = true;
        }
        else
        {
            warningPanel.SetActive(false);
        }
    }
    private void Start()
    {
        timer = 12.0f;
    }
    void Update()
    {
        verifyBtConnection();
        updateTimer();
    }

}
