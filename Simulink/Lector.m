% Lector de trayectorias mediante protocolo MQTT
%% Creación de cliente y suscripción a tópicos
clc
load('variablesLector.mat');
try
    client = mqtt("tcp://34.69.106.59"); 
catch
    disp("No se pude establecer la conexión con la dirección 34.69.106.59 ... ");
    disp("Por favor encienda el broker MQTT");
    return
end
disp("¡¡¡Conectado al servidor 34.69.106.59!!!");
susConexion = subscribe(client, "App/Conexion","QoS",2);
susEstado = subscribe(client, "App/Estado","QoS",2);
susTrayectoria = subscribe(client, "App/Trayectorias","QoS",2);
susPuntos = subscribe(client, "App/Puntos","QoS",2);
susConexion.Callback = @callbackConexion;
susEstado.Callback = @callbackAppEstado;
susPuntos.Callback = @callbackAppPuntos;
%% Conexión con aplicación móvil
intentosMax = 10;
intentosR = 0;
while(true)
    if(~conApp)
        disp("No se logró establecer la comunicación con la aplicación móvil");
        disp("Por favor inicie la aplicación ...");
    else
        disp("Conexión con App Establecida");
        publish(client, 'Dron/Conexion', 'DronConectado');
        break
    end
    intentosR = intentosR + 1;
    if(intentosR == intentosMax)
        disp("Conexión Fallida");
        return
    end
    pause(6);
end
%% Ciclo de ejecución
while conApp
    if deltaEstado
        disp(estadoApp);
        deltaEstado = false;
    end
    if puntosLeidos
        publish(client, 'Dron/Estado', 'LecturaCompletada');
        pause(4.0);
        puntosLeidos = false;
    end
    if matrizGenerada
        publish(client, 'Dron/Estado', 'PuntosProcesados');
        disp("El programa ha leido y procesado los puntos objetivo, por favor cargue el firmware al dron pulsando el boton  -build and run-");
        pause(0.5)
        programaCargado = false;
        while(~programaCargado)
            tecla = input("Por favor, oprima la tecla enter cuando haya subido el firmware al dron: ",'s');
            if(isempty(tecla))
                programaCargado = true;
                publish(client, 'Dron/Estado', 'ProgramaCargado');
            end
        end
        matrizGenerada = false;
    end
    if(programaCargado)
        programaEjecutado = false;
        while(~programaEjecutado)
            disp("Oprima el botón start en la ventana emergente para que el dron inicie su recorrido")
            tecla = input("Por favor, oprima la tecla enter cuando haya iniciado la ruta: ",'s');
            if(isempty(tecla))
                programaEjecutado = true;
                publish(client, 'Dron/Estado', 'ProgramaEjecutado');
            end
        end
    end
    if(programaEjecutado)
        programaFinalizado = false;
        while(~programaFinalizado)
            disp("Ejecutando trayectoria ... ")
            tecla = input("Por favor, oprima la tecla enter cuando haya finalizado la ejecución de la ruta: ",'s');
            if(isempty(tecla))
                programaFinalizado = true;
                publish(client, 'Dron/Estado', 'ProgramaFinalizado');
            end
        end
    end
    if(programaFinalizado)
        disp("Operación Finalizada");
        return       
    end
    if(selecPredef && ruta ~= 0 && iniciarPredef)
        rutaGen = rutaPredef(ruta);
    end
    if rutaGen
        publish(client, 'Dron/Estado', 'PredefGenerada');
        disp("La trayectoria deseada ha sido procesada, por favor cargue el firmware al dron pulsando el boton  -build and run-");
        programaCargado = false;
        while(~programaCargado)
            tecla = input("Por favor, oprima la tecla enter cuando haya subido el firmware al dron: ",'s');
            if(isempty(tecla))
                programaCargado = true;
                publish(client, 'Dron/Estado', 'ProgramaCargado');
            end
        end
        rutaGen = false;
        selecPredef = false;
    end
    pause(0.5)
end
