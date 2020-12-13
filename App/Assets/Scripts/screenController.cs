using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class screenController : MonoBehaviour
{
    private string circleButton = "joystick button 1";

    public void TutorialButton()
    {
        SceneManager.LoadScene("Tutorial");
    }
    public void InfoController()
    {
        SceneManager.LoadScene("Info");
    }
    public void BackController()
    {
        SceneManager.LoadScene("Main");
    }
    public void ButtonController()
    {
        SceneManager.LoadScene("controlScene");
    }
    public void ButtonTact()
    {
        SceneManager.LoadScene("tactScene");
    }
    public void ButtonPath()
    {
        SceneManager.LoadScene("pathScene");
    }

    void Update()
    {
        if (Input.GetKeyDown(circleButton))
        {
            BackController();
        }
    }

}