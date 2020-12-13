using System;
using System.Collections;
using System.Collections.Generic;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Text;

public class pathController : MonoBehaviour
{
    //Vectores de posición y orientación
    private Vector3 positionZero;

    //Variable que indica la ruta a realizar
    public int selectedPath;
    private bool isExecuting;

    //Variables para comunicación
    public MqttClient client;
    private bool pubState;
    public bool isDroneCon;

    //Scripts Externos
    private PassVariable passScript;
    private InstantTrackingController trackerScript;
    private MoveController dragScript;

    //UI con botones de control
    public GameObject initialCanvas;
    public GameObject UIButtons;
    public Button startBtn;

    //Elementos para ventana de advertencia
    public GameObject warningW;
    public Text warningTxt;
    private float timerWar;
    private bool actTimerWar;
    private bool resetFlag;
    private bool putWin;
    private String txtWin;

    //Indicadores de estado
    public bool active;
    public bool isInit;

    //Modelos AR
    private GameObject droneModelPrefab;
    private Transform droneModel;

    //Varibles para timer
    private float timeShadow;
    private bool timerActive;

    //Lista de posiciones objetivo y variables para visualización de trayectorias
    private List<Vector4> targetPoints = new List<Vector4>();
    private Vector3 currentPos;
    private Vector3 currentOr;
    private Vector3 targetPos;
    private float currentYaw;
    private float targetYaw;
    private bool updateTarget;
    private float sequenceTimer;
    private int indexPath;
    private bool followPos;
    private bool followZ;
    private bool followYaw;
    private float deltaX;
    private float deltaY;
    private float deltaZ;
    private float deltaYaw;
    private bool isCircle;

    public Text t;

    public void setTargetPoints()
    {
        if(selectedPath == 1)
        {
            isCircle = true;
            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(0.0f, 0.8f, 0.5f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            float r = 0.5f;
            int n = 200;
            float delta_x = 2 * r / (n / 2);
            float x = 0.0f;
            float y = 0.5f;
            float sign = 1.0f;
            float cx = 0.0f;
            float cy = 0.0f;
            float yawAux = 0.0f;
            float delYaw = 0.0f;
            for (int i = 0; i < n; i++)
            {
                cx = x - 0.5f;
                cy = y - 0.5f;
                if (cx <= 0 && cy > 0)
                {
                    delYaw = 90 - Mathf.Atan(Mathf.Abs(cx) / Mathf.Abs(cy)) * (180 / Mathf.PI);
                } else if (cx >= 0 && cy > 0)
                {
                    delYaw = 90 + Mathf.Atan(Mathf.Abs(cx) / Mathf.Abs(cy)) * (180 / Mathf.PI);
                } else if (cx >= 0 && cy < 0)
                {
                    delYaw = 270 - Mathf.Atan(Mathf.Abs(cx) / Mathf.Abs(cy)) * (180 / Mathf.PI);
                } else if (cx <= 0 && cy < 0)
                {
                    delYaw = 270 + Mathf.Atan(Mathf.Abs(cx) / Mathf.Abs(cy)) * (180 / Mathf.PI);
                }
                if (cy == 0 && cx < 0) delYaw = 0;
                if (cy == 0 && cx > 0) delYaw = 180;
                if (i == n / 2) sign = -1.0f;
                if (i < n / 2)
                {
                    y = r + Mathf.Sqrt(Mathf.Pow(r, 2) - Mathf.Pow((x - r), 2));
                }
                else
                {
                    y = r - Mathf.Sqrt(Mathf.Pow(r, 2) - Mathf.Pow((x - r), 2));
                }
                yawAux = yawZero + delYaw;
                if (yawAux >= 360) yawAux = yawAux%360;
                posAux = new Vector3(x, 0.8f, y);
                targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawAux));
                x = x + delta_x*sign;
                //Debug.Log("Yaw:" + yawAux);
                //Debug.Log("i:" + i);
                //Debug.Log("X:"+x);
                //Debug.Log("Y:" + y);

            }
        }
        else if (selectedPath == 2)
        {
            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0]+positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(0.0f, 0.8f, 1.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], 0));
            posAux = new Vector3(1.0f, 0.8f, 1.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], 90));
            posAux = new Vector3(1.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], 180));
            posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
        }
        else if (selectedPath == 3)
        {
            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(-0.5f, 0.8f, 0.5f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero+45));
            posAux = new Vector3(0.5f, 0.8f, 1.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero-45));
            posAux = new Vector3(-0.5f, 0.8f, 1.5f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero+45));
            posAux = new Vector3(0.5f, 0.8f, 2.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero-45));

        }
        else if (selectedPath == 4)
        {
            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(-0.5f, 0.8f, 0.5f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(-1.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
        }
        else if (selectedPath == 5)
        {
            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(0.0f, 0.8f, 1.5f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
        }
        else if (selectedPath == 6)
        {

            positionZero = trackerScript.model.position;
            float yawZero = trackerScript.model.eulerAngles[1]; //270
            targetPoints.Add(new Vector4(positionZero[0], positionZero[1], positionZero[2], yawZero));
            Vector3 posAux = new Vector3(0.0f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
            posAux = new Vector3(1.5f, 0.8f, 0.0f);
            targetPoints.Add(new Vector4(posAux[0] + positionZero[0], posAux[1] + positionZero[1], posAux[2] + positionZero[2], yawZero));
        }
    }

    public void removeModels()
    {
        //Función para retirar los modelos AR de la pantalla
        foreach (var modelAux in trackerScript._activeModels)
        {
            if (modelAux)
            {
                modelAux.SetActive(false);
            }
        }
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
        if (timerActive)
        {
            timeShadow -= Time.deltaTime;
        }
        if (Mathf.Abs(timeShadow) < 0.1)
        {
            removeModels();
            droneModel.localScale = new Vector3(1.0f, 1.0f, 1.0f);
            timerActive = false;
            timeShadow = 0.7f;
        }
        if (isExecuting)
        {
            sequenceTimer -= Time.deltaTime;
        }
        if (Mathf.Abs(sequenceTimer) < 0.05)
        {
            if (Mathf.Abs(targetPos[1] - currentPos[1]) > 0.015 && followZ)
            {
                currentPos[1] += deltaZ;
            }
            if (Mathf.Abs(targetPos[0] - currentPos[0]) > 0.015 && followPos)
            {
                currentPos[0] += deltaX;
                if(!isCircle) currentOr[0] = -12.0f * Mathf.Sign(deltaX);
            }
            else
            {
                currentOr[0] = 0.0f;
            }

            if (Mathf.Abs(targetPos[2] - currentPos[2]) > 0.015 && followPos)
            {
                currentPos[2] += deltaY;
                if (!isCircle)  currentOr[2] = -12.0f * Mathf.Sign(deltaY);
            }
            else
            {
                currentOr[2] = 0.0f;
            }
            if (Mathf.Abs(targetYaw - currentYaw) > 5.0 && followYaw)
            {
                currentOr[1] += deltaYaw;
            }
            droneModel.eulerAngles = currentOr;
            droneModel.position = currentPos;
            sequenceTimer = 0.15f;
        }

    }

    public void startButton()
    {
        //Función que se ejecuta al oprimir el boton start, se comunica con la estación del dron para iniciar la trayectoria

        client.Publish("App/Estado", Encoding.ASCII.GetBytes("IniciarPredef"));
        dragScript.isActive = false;
        initialCanvas.SetActive(false);
        setTargetPoints();
        startBtn.interactable = false;
        if (!isInit)
        {
            positionZero = trackerScript.model.position;
            droneModelPrefab = trackerScript.Models[0];
            droneModel = Instantiate(droneModelPrefab).transform;
            droneModel.position = trackerScript.model.position;
            droneModel.eulerAngles = trackerScript.model.eulerAngles;
            removeModels();
            droneModel.localScale = new Vector3(0.001f, 0.001f, 0.001f);
            GameObject modelPrefab = trackerScript.Models[1];
            Transform model = Instantiate(modelPrefab).transform;
            model.position = droneModel.position;
            model.eulerAngles = droneModel.eulerAngles;
            trackerScript._activeModels.Add(model.gameObject);
            timerActive = true;
            /*
            isExecuting = true;
            indexPath = 0;
            followPos = false;
            followZ = true;
            followYaw = false;
            updateTarget = true;
            */
        }
        isInit = true;
    }

    public void executePath()
    {
        if (updateTarget)
        {
            sequenceTimer = 0.15f;
            currentPos = new Vector3(targetPoints[indexPath][0], targetPoints[indexPath][1], targetPoints[indexPath][2]);
            currentYaw = targetPoints[indexPath][3];
            targetYaw = targetPoints[indexPath + 1][3];
            currentOr = new Vector3(0.0f, currentYaw, 0.0f);
            targetPos = new Vector3(targetPoints[indexPath + 1][0], targetPoints[indexPath + 1][1], targetPoints[indexPath + 1][2]);
            droneModel.position = currentPos;
            droneModel.eulerAngles = currentOr;
            if (targetPos[0] < currentPos[0]) deltaX = -0.028f; else deltaX = 0.028f;
            if (targetPos[2] < currentPos[2]) deltaY = -0.028f; else deltaY = 0.028f;
            if (targetPos[1] < currentPos[1]) deltaZ = -0.028f; else deltaZ = 0.028f;
            if (targetYaw < currentYaw) deltaYaw = -4.5f; else deltaYaw = 4.5f;
            if (targetPos[1] == 0)
            {
                followPos = true;
                followZ = false;
                followYaw = false;
            }
            updateTarget = false;
        }
        if (followZ)
        {
            float currentAltitude = droneModel.position[1];
            float targetAltitude = targetPos[1];
            float altitudeError = Mathf.Abs(targetAltitude - currentAltitude);
            if (isExecuting && altitudeError < 0.015)
            {
                if (targetPos[1] == 0)
                {
                    indexPath += 1;
                    if (indexPath < targetPoints.Count - 1)
                    {
                        updateTarget = true;
                        followPos = false;
                        followZ = true;
                        followYaw = false;
                    }
                    else
                    {
                        isExecuting = false;
                        removeModels();
                        followPos = false;
                        followZ = false;
                        followYaw = false;
                    }
                }
                else
                {
                    followPos = true;
                    followZ = false;
                    followYaw = false;
                }
            }
        }
        if (followPos)
        {
            float currentX = droneModel.position[0];
            float targetX = targetPos[0];
            float xError = Mathf.Abs(targetX - currentX);
            float currentY = droneModel.position[2];
            float targetY = targetPos[2];
            float yError = Mathf.Abs(targetY - currentY);
            if (isExecuting && xError < 0.015 && yError < 0.015)
            {
                followPos = false;
                followZ = false;
                followYaw = true;
            }
        }
        if (followYaw)
        {
            currentYaw = droneModel.eulerAngles[1];
            float yawError = Mathf.Abs(targetYaw - currentYaw);
            if (isExecuting && yawError < 5.0)
            {
                if (targetPos[1] != 0) indexPath += 1;
                if (indexPath < targetPoints.Count - 1)
                {
                    if (targetPos[1] == 0) updateTarget = false; else updateTarget = true;
                    followPos = false;
                    followZ = true;
                    followYaw = false;
                }
                else
                {
                    isExecuting = true;
                    followPos = false;
                    followZ = true;
                    followYaw = false;
                    updateTarget = true;
                    indexPath = 0;
                }

            }
        }
    }


    public void Client_recievedMessage(object sender, MqttMsgPublishEventArgs e)
    {
        //Función que se ejecuta al recibir un mensaje en un tópico en donde hay una suscripción
        String message = System.Text.Encoding.Default.GetString(e.Message);
        if (e.Topic == "Dron/Estado" && message == "PredefGenerada")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "La estación ha recibido la información de la ruta seleccionada, en espera de carga y ejecución";
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaCargado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El programa ha sido cargado al dron, en espera de inicio de la ruta";
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaEjecutado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El dron ha iniciado la ejecución de la ruta deseada";
            isExecuting = true;
            indexPath = 0;
            followPos = false;
            followZ = true;
            followYaw = false;
            updateTarget = true;
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaFinalizado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El dron ha finalizado la ejecución de la ruta deseada";
            isExecuting = false;
            resetFlag = true;
        }

    }

    public void subscriptions()
    {
        //Función que suscribe al cliente a los tópicos requeridos
        client.Subscribe(new String[] { "Dron/Estado" }, new byte[] { MqttMsgBase.QOS_LEVEL_EXACTLY_ONCE });
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
        isExecuting = false;
        active = false;
        isInit = false;
        timerActive = false;
        updateTarget = false;
        followPos = false;
        followZ = true;
        followYaw = false;
        isCircle = false;

        passScript = GameObject.Find("PassVariable").gameObject.GetComponent<PassVariable>();
        dragScript = GameObject.Find("Controller").gameObject.GetComponent<MoveController>();
        trackerScript = GameObject.Find("Controller").gameObject.GetComponent<InstantTrackingController>();
        selectedPath = passScript.getSP();

        //setTargetPoints();
        isDroneCon = passScript.getConState();

        subscriptions();
        timerWar = 3.5f;
        timeShadow = 0.7f;
        sequenceTimer = 1.0f;
        deltaX = 0.028f;
        deltaY = 0.028f;
        deltaZ = 0.028f;
        deltaYaw = 4.5f;
        indexPath = 0;
    }

    void Update()
    {
        updateTimers();
        active = !(trackerScript.InitializeButton.IsActive() || trackerScript.ButtonDock.activeInHierarchy);
        if (active) UIButtons.SetActive(true); else UIButtons.SetActive(false);
        if (isInit && isExecuting)
        {
            executePath();
        }
        if (isDroneCon && !pubState)
        {
            string pubData = "RutPredefinida" + selectedPath.ToString();
            client.Publish("App/Estado", Encoding.ASCII.GetBytes(pubData));
            pubState = true;
        }
        if (putWin)
        {
            actTimerWar = true;
            warningW.SetActive(true);
            warningTxt.text = txtWin;
            putWin = false;
        }

    }
}
