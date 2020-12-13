using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class tutorialController : MonoBehaviour
{
    public GameObject panel1;
    public GameObject panel2;
    public GameObject panel3;
    public GameObject panel4;
    public GameObject panel5;
    public GameObject panel6;
    public GameObject panel7;
    public GameObject panel8;
    public GameObject panel9;
    public GameObject panel10;
    public GameObject panel11;

    public void rigthP1()
    {
        panel1.SetActive(false);
        panel2.SetActive(true);
    }
    public void leftP2()
    {
        panel1.SetActive(true);
        panel2.SetActive(false);
    }
    public void rigthP2()
    {
        panel2.SetActive(false);
        panel3.SetActive(true);
    }
    public void leftP3()
    {
        panel2.SetActive(true);
        panel3.SetActive(false);
    }
    public void rigthP3()
    {
        panel3.SetActive(false);
        panel4.SetActive(true);
    }
    public void leftP4()
    {
        panel3.SetActive(true);
        panel4.SetActive(false);
    }
    public void rigthP4()
    {
        panel4.SetActive(false);
        panel5.SetActive(true);
    }
    public void leftP5()
    {
        panel4.SetActive(true);
        panel5.SetActive(false);
    }
    public void rigthP5()
    {
        panel5.SetActive(false);
        panel6.SetActive(true);
    }
    public void leftP6()
    {
        panel5.SetActive(true);
        panel6.SetActive(false);
    }
    public void rigthP6()
    {
        panel6.SetActive(false);
        panel7.SetActive(true);
    }
    public void leftP7()
    {
        panel6.SetActive(true);
        panel7.SetActive(false);
    }
    public void rigthP7()
    {
        panel7.SetActive(false);
        panel8.SetActive(true);
    }
    public void leftP8()
    {
        panel7.SetActive(true);
        panel8.SetActive(false);
    }
    public void rigthP8()
    {
        panel8.SetActive(false);
        panel9.SetActive(true);
    }
    public void leftP9()
    {
        panel8.SetActive(true);
        panel9.SetActive(false);
    }
    public void rigthP9()
    {
        panel9.SetActive(false);
        panel10.SetActive(true);
    }
    public void leftP10()
    {
        panel9.SetActive(true);
        panel10.SetActive(false);
    }
    public void rigthP10()
    {
        panel10.SetActive(false);
        panel11.SetActive(true);
    }
    public void leftP11()
    {
        panel10.SetActive(true);
        panel11.SetActive(false);
    }

    void Start()
    {
        panel1.SetActive(true);
    }

    void Update()
    {
        
    }
}
