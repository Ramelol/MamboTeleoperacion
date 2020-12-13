using System;
using System.Collections;
using System.Collections.Generic;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Text;

public class moveController : MonoBehaviour
{

    //Creación de Cliente MQTT
    public MqttClient client;
    public bool isDroneCon;
    private bool pubState;
    private bool pointsUpload;
    private bool isDroneExecutingPath;

    //Elementos para ventana de advertencia
    public GameObject warningW;
    public Text warningTxt;
    private float timerWar;
    private bool actTimerWar;
    private bool resetFlag;
    private bool putWin;
    private String txtWin;

    //Scripts externos
    private InstantTrackingController trackerScript;
    private MoveController dragScript;

    //Vectores de posición y orientación
    private Vector3 positionZero;
    private Vector3 initialPos;
    private Vector3 currentPos;
    private Vector3 currentOr;

    //Posición y orientación del sistema de referencias global
    private Vector3 positionWR;
    private Vector3 orientationWR;

    //Contador de puntos objetivo seleccionados
    private int xCount;

    //Indicadores de estado
    public bool active;
    private bool isFlying;
    private bool isInit;

    //Variables para control de velocidad del modelo
    private float deltaV;
    private float vel;
    public Slider velSlider;
    public GameObject sliderCont;

    //Modelos AR
    private GameObject droneModelPrefab;
    private Transform droneModel;
    private GameObject shPathPrefab;
    private Transform modelShPath;
    public int droneCode;

    //Textos
    public Text txtVel;
    public Text textX;
    public Text textY;
    public Text textZ;
    public Text textYaw;
    public GameObject labelCont;

    //Variables para vizualización de coordenadas
    private bool variablesActive;
    private int contView;
    private bool isViewRS;

    //Lista de posiciones objetivo
    private List<Vector4> targetPoints = new List<Vector4>();
    private List<Vector4> targetPointsWR = new List<Vector4>();

    //Variables para control de tiempos
    private bool timerActive;
    private float timeShadow;
    private bool velTimerActive;
    private float timeVel;
    private bool isExecutingPath;
    private float sequenceTimer;

    //Variables para visualización de trayectorias
    private int indexPath;
    private float deltaX;
    private float deltaY;
    private float deltaZ;
    private float deltaYaw;
    private bool followPos;
    private bool followZ;
    private bool followYaw;
    private Vector3 currentPosShadow;
    private Vector3 currentOrShadow;
    private Vector3 targetPosShadow;
    private float currentYawShadow;
    private float targetYawShadow;
    private bool updateTarget;

    //Variables de entrada de joysticks
    private float xL; 
    private float yL; 
    private float xR; 
    private float yR;

    //Variables para lectura de control bluetooth 
    private string xButton = "joystick button 0";
    private string cButton = "joystick button 2";
    private string L1Button = "joystick button 4";
    private string R1Button = "joystick button 5";
    private string L2Button = "joystick button 6";
    private string R2Button = "joystick button 7";
    private string psButton = "joystick button 12";

    public void pathButton()
    {
        //Función que se ejecuta al pulsar el botón 'cuadrado' para observar la trayectoría
        if (targetPoints.Count >= 2)
        {
            isExecutingPath = true;
            followPos = false;
            followZ = true;
            followYaw = false;
            indexPath = 0;
            updateTarget = true;
        }
    }

    public void followTPoints()
    {
        //Función que muestra el recorrido formado por los puntos objetivo
        if (isExecutingPath && updateTarget)
        {
            removeModels();
            sequenceTimer = 0.10f;
            currentPosShadow = new Vector3(targetPoints[indexPath][0], targetPoints[indexPath][1], targetPoints[indexPath][2]);
            currentYawShadow = targetPoints[indexPath][3];
            targetYawShadow = targetPoints[indexPath + 1][3];
            currentOrShadow = new Vector3(0.0f, currentYawShadow, 0.0f);
            targetPosShadow = new Vector3(targetPoints[indexPath + 1][0], targetPoints[indexPath + 1][1], targetPoints[indexPath + 1][2]);
            modelShPath = Instantiate(shPathPrefab).transform;
            trackerScript._activeModels.Add(modelShPath.gameObject);
            modelShPath.position = currentPosShadow;
            modelShPath.eulerAngles = currentOrShadow;
            if (targetPosShadow[0] < currentPosShadow[0]) deltaX = -0.028f; else deltaX = 0.028f;
            if (targetPosShadow[2] < currentPosShadow[2]) deltaY = -0.028f; else deltaY = 0.028f;
            if (targetPosShadow[1] < currentPosShadow[1]) deltaZ = -0.028f; else deltaZ = 0.028f;
            if (targetYawShadow < currentYawShadow) deltaYaw = -4.5f; else deltaYaw = 4.5f;
            if (targetPosShadow[1] == 0)
            {
                followPos = true;
                followZ = false;
                followYaw = false;
            }
            updateTarget = false;
        }
        if (followZ)
        {
            float currentAltitude = modelShPath.position[1];
            float targetAltitude = targetPosShadow[1];
            float altitudeError = Mathf.Abs(targetAltitude - currentAltitude);
            if (isExecutingPath && altitudeError < 0.015)
            {
                if (targetPosShadow[1] == 0)
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
                        isExecutingPath = false;
                        removeModels();
                        if (variablesActive) putWRModel();
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
            float currentX = modelShPath.position[0];
            float targetX = targetPosShadow[0];
            float xError = Mathf.Abs(targetX - currentX);
            float currentY = modelShPath.position[2];
            float targetY = targetPosShadow[2];
            float yError = Mathf.Abs(targetY - currentY);
            if (isExecutingPath && xError < 0.015 && yError < 0.015)
            {
                followPos = false;
                followZ = false;
                followYaw = true;
            }
        }
        if (followYaw)
        {
            currentYawShadow = modelShPath.eulerAngles[1];
            float yawError = Mathf.Abs(targetYawShadow - currentYawShadow);
            if (isExecutingPath && yawError < 5.0)
            {
                if (targetPosShadow[1] != 0) indexPath += 1;
                if (indexPath < targetPoints.Count - 1)
                {
                    if (targetPosShadow[1] == 0) updateTarget = false; else updateTarget = true;
                    followPos = false;
                    followZ = true;
                    followYaw = false;
                }
                else
                {
                    isExecutingPath = false;
                    removeModels();
                    if (variablesActive) putWRModel();
                    followPos = false;
                    followZ = false;
                    followYaw = false;
                    if (isDroneExecutingPath) pathButton();
                }
            }
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

    public void putWRModel()
    {
        //Ubica el objeto AR del sistema de coordenadas en la pantalla
        GameObject modelPrefab = trackerScript.Models[2];
        Transform modelR = Instantiate(modelPrefab).transform;
        modelR.position = positionZero;
        modelR.eulerAngles = new Vector3(0.0f, 90.0f, 0.0f);
        if (variablesActive)
        {
            trackerScript._activeModels.Add(modelR.gameObject);
        }
    }


    public void updateTimers()
    {
        //Función para el control de temporizadores
        if (isExecutingPath)
        {
            sequenceTimer -= Time.deltaTime;
        }
        if (Mathf.Abs(sequenceTimer) < 0.05)
        {
            if (Mathf.Abs(targetPosShadow[1] - currentPosShadow[1]) > 0.015 && followZ)
            {
                currentPosShadow[1] += deltaZ;
            }
            if (Mathf.Abs(targetPosShadow[0] - currentPosShadow[0]) > 0.015 && followPos)
            {
                currentPosShadow[0] += deltaX;
                currentOrShadow[0] = -12.0f * Mathf.Sign(deltaX);
            }
            else
            {
                currentOrShadow[0] = 0.0f;
            }

            if (Mathf.Abs(targetPosShadow[2] - currentPosShadow[2]) > 0.015 && followPos)
            {
                currentPosShadow[2] += deltaY;
                currentOrShadow[2] = -12.0f * Mathf.Sign(deltaY);
            }
            else
            {
                currentOrShadow[2] = 0.0f;
            }
            if (Mathf.Abs(targetYawShadow - currentYawShadow) > 5.0 && followYaw)
            {
                currentOrShadow[1] += deltaYaw;
            }
            modelShPath.eulerAngles = currentOrShadow;
            modelShPath.position = currentPosShadow;
            sequenceTimer = 0.10f;
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
        if (velTimerActive)
        {
            timeVel -= Time.deltaTime;
        }
        if (Mathf.Abs(timeVel) < 0.1)
        {
            sliderCont.SetActive(false);
            velTimerActive = false;
            timeVel = 3.0f;
        }
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

    public void xLecture()
    {
        //Función que revisa si se pulso el botón 'x' y ubica un punto objetivo.
        active = !trackerScript.ButtonDock.activeInHierarchy;
        if (active)
        {
            if (Input.GetKeyDown(xButton))
            {
                xCount = xCount + 1;
                if (xCount == 1)
                {
                    droneModelPrefab = trackerScript.Models[0];
                    droneModel = Instantiate(droneModelPrefab).transform;
                    droneModel.position = trackerScript.model.position;
                    droneModel.eulerAngles = trackerScript.model.eulerAngles;
                }
                removeModels();
                droneModel.localScale = new Vector3(0.001f, 0.001f, 0.001f);
                GameObject modelPrefab = trackerScript.Models[1];
                Transform model = Instantiate(modelPrefab).transform;
                model.position = droneModel.position;
                model.eulerAngles = droneModel.eulerAngles;
                currentPos = model.position;
                currentOr = model.eulerAngles;
                trackerScript._activeModels.Add(model.gameObject);
                timerActive = true;
                Vector3 vectAx = currentPos - positionZero;
                Vector4 posAux = new Vector4(droneModel.position[0], droneModel.position[1], droneModel.position[2], droneModel.eulerAngles[1]);
                Vector4 posAuxWR = new Vector4(vectAx[0], vectAx[2], vectAx[1], (posAux[3] + 90) % 360);
                targetPoints.Add(posAux);
                targetPointsWR.Add(posAuxWR);
            }
        }

        if (xCount == 1)
        {
            dragScript.isActive = false;
            if (!isInit) positionZero = trackerScript.model.position;
            isInit = true;
        }

    }
    public void movementController()
    {
        //Función que lee los movimientos en los joysticks y transforma las coordenadas del dron en AR
        xL = Input.GetAxis("Horizontal");
        yL = Input.GetAxis("Vertical");

        xR = Input.GetAxis("xR");
        yR = Input.GetAxis("yR");

        if (!isFlying && yL > 0) isFlying = true;

        if (isFlying) {

            float roll = 0;
            float pitch = 0;

            if (Mathf.Abs(xR) >= 0.1)
            {
                roll = -12.0f * Mathf.Sign(xR);
            }
            else
            {
                roll = 0;
            }

            if (Mathf.Abs(yR) >= 0.1)
            {
                pitch = -12.0f * Mathf.Sign(yR);
            }
            else
            {
                pitch = 0;
            }

            currentOr = droneModel.eulerAngles;
            currentPos = droneModel.position;

            Vector3 deltaOr = new Vector3(0.0f, 5.0f * xL * vel, 0.0f);
            Vector3 newOr = currentOr;
            float theta;
            float dX = 0;
            float dY = 0;
            if (currentPos[1] != 0)
            {
                newOr = currentOr + deltaOr;
                newOr[0] = roll;
                newOr[2] = pitch;
                theta = newOr[1];
                dX = yR * Mathf.Cos(theta * Mathf.PI / 180) - xR * Mathf.Sin(theta * Mathf.PI / 180);
                dY = -yR * Mathf.Sin(theta * Mathf.PI / 180) - xR * Mathf.Cos(theta * Mathf.PI / 180);
            }


            Vector3 deltaPos = new Vector3(0.12f * dX * vel, 0.12f * yL * vel, 0.12f * dY * vel);
            Vector3 newPos = currentPos + deltaPos;
            if (newPos[1] >= 1.8) newPos[1] = 1.8f;
            if (newPos[1] <= 0) newPos[1] = 0;
            droneModel.SetPositionAndRotation(newPos, Quaternion.Euler(newOr));
            Vector3 aux = newPos - positionZero;
            textX.text = "x: " + aux[0].ToString("0.##") + "m";
            textY.text = "y: " + aux[2].ToString("0.##") + "m";
            textZ.text = "z: " + aux[1].ToString("0.##") + "m";
            textYaw.text = "yaw: " + ((newOr[1] + 90) % 360).ToString("0.##") + "°";
        }
    }
    public void viewVariables()
    {
        //Activa o desactiva la visualización del sistema de coordenadas
        if (variablesActive)
        {
            putWRModel();
        }
        if (Input.GetKeyDown(R1Button))
        {
            if (isInit)
            {
                if (contView % 2 == 0 && !isViewRS)
                {
                    variablesActive = true;
                    labelCont.SetActive(true);
                    isViewRS = true;
                }
                else if (contView % 2 == 0 && isViewRS)
                {
                    labelCont.SetActive(true);
                    removeModels();
                    variablesActive = false;
                    isViewRS = false;
                    contView += 1;
                }
                else
                {
                    removeModels();
                    variablesActive = false;
                    labelCont.SetActive(false);
                    isViewRS = false;
                    contView += 1;
                }
            }
        }
    }

    public void velController()
    {
        if (Input.GetKeyDown(L2Button))
        {
            sliderCont.SetActive(true);
            velSlider.value = velSlider.value - deltaV;
            velTimerActive = true;
            timeVel = 3.0f;
        }
        if (Input.GetKeyDown(R2Button))
        {
            sliderCont.SetActive(true);
            velSlider.value = velSlider.value + deltaV;
            velTimerActive = true;
            timeVel = 3.0f;
        }
        if (velSlider.value < 0) velSlider.value = 0;
        if (velSlider.value > 1) velSlider.value = 1;
        txtVel.text = (velSlider.value * 100).ToString() + " %";
        vel = velSlider.value;
    }

    public String vectorToString(List<Vector4> vec)
    {
        String data = "";
        for (int i = 0; i < vec.Count; i++)
        {
            data += vec[i].ToString();
            data += " ";
        }
        return data;
    }

    public void Client_recievedMessage(object sender, MqttMsgPublishEventArgs e)
    {
        //Función que se ejecuta al recibir un mensaje en un tópico en donde hay una suscripciónS
        //Debug.Log("aaaaaa");
        String message = System.Text.Encoding.Default.GetString(e.Message);
        if (e.Topic == "Dron/Estado" && message == "LecturaCompletada")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "La estación del drón realizó la lectura de datos, en espera de procesamiento de datos";
            pointsUpload = true;
        }
        if (e.Topic == "Dron/Estado" && message == "PuntosProcesados")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "La estación del drón realizó el procesamiento de datos, en espera de carga del programa al dron";
            pointsUpload = true;
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaCargado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El programa ha sido cargado al dron, en espera de inicio de la ruta";
            pointsUpload = true;
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaEjecutado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El dron ha iniciado la ejecución de la ruta deseada";
            pointsUpload = true;
            isDroneExecutingPath = true;
            pathButton();
        }
        if (e.Topic == "Dron/Estado" && message == "ProgramaFinalizado")
        {
            actTimerWar = true;
            putWin = true;
            txtWin = "El dron ha finalizado la ejecución de la ruta deseada";
            pointsUpload = true;
            isDroneExecutingPath = false;
            resetFlag = true;
        }
    }

    public void uploadPoints()
    {
        //Función que publica los puntos objetivo en el tópico "Dron/Posiciones", se ejecuta al pulsar el botón start
        if (!pointsUpload && Input.GetKeyDown(psButton))
        {
            String points = vectorToString(targetPointsWR);
            client.Publish("App/Puntos", Encoding.ASCII.GetBytes(points));
            client.Publish("App/Estado", Encoding.ASCII.GetBytes("PuntosSubidos"));
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
            resetFlag = false;
            warningW.SetActive(true);
            warningTxt.text = "¡¡¡Conectado al servidor 34.69.106.59!!!";
        }
        catch
        {
            actTimerWar = true;
            resetFlag = false;
            warningW.SetActive(true);
            warningTxt.text = "No se pudo establecer conexión con la dirección 34.69.106.59 !!!";
        }

        updateTarget = false;
        isExecutingPath = false;
        variablesActive = false;
        followPos = false;
        followZ = false;
        followYaw = false;
        isFlying = false;
        isInit = false;
        timerActive = false;
        velTimerActive = false;
        pubState = false;
        putWin = false;
        pointsUpload = false;
        isViewRS = false;
        resetFlag = false;
        velSlider.interactable = false;
        isDroneExecutingPath = false;
        labelCont.SetActive(false);
        sliderCont.SetActive(false);

        indexPath = 0;
        xCount = 0;
        contView = 0;

        deltaX = 0.028f;
        deltaY = 0.028f;
        deltaZ = 0.028f;
        deltaYaw = 4.5f;
        deltaV = 0.1f;
        vel = 0.5f;
        timeShadow = 0.7f;
        timeVel = 3.0f;
        timerWar = 3.5f;
        sequenceTimer = 1.0f;
        velSlider.value = 0.5f;

        textX.text = "0.0 m";
        textY.text = "0.0 m";
        textZ.text = "0.0 m";
        textYaw.text = "0 °";
        txtWin = "";

        trackerScript = GameObject.Find("Controller").gameObject.GetComponent<InstantTrackingController>();
        dragScript = GameObject.Find("Controller").gameObject.GetComponent<MoveController>();
        shPathPrefab = trackerScript.Models[1];
        isDroneCon = false;

        subscriptions();
    }
    void Update()
    {
        updateTimers();
        xLecture();
        if (isInit)
        {
            if (!pointsUpload) movementController();
            velController();
            viewVariables();
            if (Input.GetKeyDown(cButton))
            {
                pathButton();
            }
            followTPoints();
            trackerScript.ButtonDock.SetActive(false);
            trackerScript._gridRenderer.enabled = false;
            uploadPoints();
        }
        if (isDroneCon && !pubState)
        {
            client.Publish("App/Estado", Encoding.ASCII.GetBytes("ContIniciada"));
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
