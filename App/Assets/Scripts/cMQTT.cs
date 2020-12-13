using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using System.Text;
using UnityEngine.UI;
using System;

public class cMQTT : MonoBehaviour
{

    //Creación de Cliente MQTT
    public MqttClient client;

    //Variables de verificacion de conexión con MQTT y con Dron 
    private bool isConected;
    public static bool isTalking;

    //Elementos para ventana de advertencia
    public GameObject warningW;
    public Text warningTxt;
    private float timerWar;
    private bool actTimerWar;

    //Variables para timer de publicación
    private float timerPub;
    private bool actTimerPub;

    //Script para enviar variables entre escenas
    private PassVariable passScript;



    public void Client_recievedMessage(object sender, MqttMsgPublishEventArgs e)
    {
        String message = System.Text.Encoding.Default.GetString(e.Message);
        if (e.Topic == "Dron/Conexion" && message == "DronConectado")
        {
            isTalking = true;
            client.Publish("App/Estado", Encoding.ASCII.GetBytes("AppIniciada"));
            passScript.isTalkingAux = true;
        }

    }
    public void updateTimer()
    {
        if (actTimerWar)
        {
            timerWar -= Time.deltaTime;
        }
        if (Mathf.Abs(timerWar) < 0.1)
        {
            actTimerWar = false;
            timerWar = 2.7f;
            warningW.SetActive(false);
        }
        if (actTimerPub && isConected)
        {
            timerPub -= Time.deltaTime;
        }
        if (Mathf.Abs(timerPub) < 0.1)
        {
            client.Publish("App/Conexion", Encoding.ASCII.GetBytes("AppConectada"));
            timerPub = 1.0f;
        }
    }
    void Start()
    {
        try
        {
            client = new MqttClient("34.69.106.59");
            client.Connect("id");
            client.MqttMsgPublishReceived += Client_recievedMessage;
            actTimerWar = true;
            warningW.SetActive(true);
            warningTxt.text = "¡¡¡Conectado al servidor 34.69.106.59!!!";
            client.Subscribe(new String[] { "Dron/Conexion" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
            isConected = true;
        }
        catch
        {
            actTimerWar = true;
            warningW.SetActive(true);
            isConected = false;
            warningTxt.text = "No se pudo establecer conexión con la dirección 34.69.106.59 !!!";
        }
        timerWar = 2.7f;
        timerPub = 1.0f;
        actTimerPub = true;
        passScript = GameObject.Find("PassVariable").gameObject.GetComponent<PassVariable>();
    }
    void Update()
    {
        updateTimer();
        if (isTalking)
        {
            warningW.SetActive(true);
            warningTxt.text = "¡¡¡Conexión establecida con la estación del dron!!!";
            actTimerWar = true;
            timerWar = 2.7f;
            isTalking = false;
        }
        
    }
}
