using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PassVariable : MonoBehaviour
{
    //Variables para la verificación de la comunicación
    public static bool isTalking = false;
    public bool isTalkingAux = false;

    //Variables para seleccionar la ruta predefinida que se desea
    public static int selectedPath = 0;
    public bool isChangedSP = false;
    public int auxSelectedPath = 0;

    //Scripts Externos
    private tactController tactScript;
    private moveController contScript;

    public int getSP()
    {
        return selectedPath;
    }

    public bool getConState()
    {
        return isTalking;
    }

    public void Start()
    {
        try
        {
            tactScript = GameObject.Find("moveController").gameObject.GetComponent<tactController>();
        }
        catch { }
        try
        {
            contScript = GameObject.Find("MoveController").gameObject.GetComponent<moveController>();
        }
        catch { }  
    }

    private void Update()
    {
        if (isTalkingAux)
        {
            isTalking = isTalkingAux;
        }
        try
        {
            tactScript.isDroneCon = isTalking;
        }
        catch { }
        try
        {
            contScript.isDroneCon = isTalking;
        }
        catch { }
        if (isChangedSP)
        {
            selectedPath = auxSelectedPath;
            isChangedSP = false;
        }
    }
}
