using System;
using System.Collections;
using System.Collections.Generic;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Text;

public class buttonsPaths : MonoBehaviour
{
    // Script externo para enviar y recibir variables entre escenas
    private PassVariable passScript;

    //Variables para comunicación
    public MqttClient client;
    private bool pubState;
    public bool isDroneCon;

    //Elementos para ventana de advertencia
    public GameObject warningW;
    public Text warningTxt;
    private float timerWar;
    private bool actTimerWar;
    private bool resetFlag;
    private bool putWin;
    private String txtWin;


    // Eventos de los botones
    public void circleButton()
    {
        passScript.auxSelectedPath = 1;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }
    public void sqrButton()
    {
        passScript.auxSelectedPath = 2;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }
    public void zigButton()
    {
        passScript.auxSelectedPath = 3;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }
    public void triButton()
    {
        passScript.auxSelectedPath = 4;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }
    public void frontButton()
    {
        passScript.auxSelectedPath = 5;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }
    public void rigthButton()
    {
        passScript.auxSelectedPath = 6;
        passScript.isChangedSP = true;
        SceneManager.LoadScene("arPathScene");
    }

    public void Client_recievedMessage(object sender, MqttMsgPublishEventArgs e)
    {
        //Función que se ejecuta al recibir un mensaje en un tópico en donde hay una suscripción
    }

    public void subscriptions()
    {
        //Función que suscribe al cliente a los tópicos requeridos
        client.Subscribe(new String[] { "Dron/Estado" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
    }

    public void updateTimers()
    {
        //Función que administra los temporizadores
        if (actTimerWar)
        {
            timerWar -= Time.deltaTime;
        }
        if (Mathf.Abs(timerWar) < 0.1)
        {
            actTimerWar = false;
            timerWar = 3.5f;
            warningW.SetActive(false);
            if (resetFlag)
            {
                SceneManager.LoadScene("Main");
            }
        }
    }

    void Start()
    {
        //Inicialización de variables
        try
        {
            client = new MqttClient("34.69.106.59");
            client.Connect("id");
            client.MqttMsgPublishReceived += Client_recievedMessage;
            actTimerWar = true;
            warningW.SetActive(true);
            resetFlag = false;
            warningTxt.text = "¡¡¡Conectado al servidor 34.69.106.59!!!";
        }
        catch
        {
            actTimerWar = true;
            resetFlag = false;
            warningW.SetActive(true);
            warningTxt.text = "No se pudo establecer conexión con la dirección 34.69.106.59 !!!";
        }

        pubState = false;

        passScript = GameObject.Find("PassVariable").gameObject.GetComponent<PassVariable>();
        isDroneCon = passScript.getConState();

        subscriptions();
        timerWar = 3.5f;
    }

    void Update()
    {
        updateTimers();
        if (isDroneCon && !pubState)
        {
            client.Publish("App/Estado", Encoding.ASCII.GetBytes("RutPredefinidas"));
            pubState = true;
        }

    }
}
