function callbackAppEstado(topic, msg)
    %fprintf('MQTT callback topic "%s": "%s"\n', topic, msg)
    if(msg=="AppIniciada")
        assignin('base','estadoApp','La aplicación se ha iniciado y el usuario está en la ventana principal');
        assignin('base','deltaEstado',true);
    elseif(msg=="TactIniciada")
        assignin('base','estadoApp','El usuario ha ingresado a la ventana de definición de trayectorias con botones en pantalla');
        assignin('base','deltaEstado',true);
        assignin('base','modoOperacion',1);
        assignin('base','selecPredef',false);
    elseif(msg=="ContIniciada")
        assignin('base','estadoApp','El usuario ha ingresado a la ventana de definición de trayectorias con control bluetooth');
        assignin('base','deltaEstado',true);
        assignin('base','modoOperacion',1);
        assignin('base','selecPredef',false);
    elseif(msg=="PuntosSubidos")
        assignin('base','estadoApp','¡Lectura de puntos objetivo completada!');
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinidas")
        assignin('base','estadoApp','El usuario ha ingresado a la ventana de selección de trayectorias predefinidas');
        assignin('base','selecPredef',true);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida1")
        assignin('base','estadoApp','Se ha seleccionado la trayectoria circular');
        assignin('base','ruta',1);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida2")
        assignin('base','estadoApp','Se ha seleccionado la trayectoria cuadrada');
        assignin('base','ruta',2);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida3")
        assignin('base','estadoApp','Se ha seleccionado la trayectoria en zig-zag');
        assignin('base','ruta',3);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida4")
        assignin('base','estadoApp','Se ha seleccionado la trayectoria triangular');
        assignin('base','ruta',4);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida5")
        assignin('base','estadoApp','Se ha seleccionado el movimiento de avance');
        assignin('base','ruta',5);
        assignin('base','deltaEstado',true);
    elseif(msg=="RutPredefinida6")
        assignin('base','estadoApp','Se ha seleccionado el movimiento a la derecha');
        assignin('base','ruta',6);
        assignin('base','deltaEstado',true);
    elseif(msg=="IniciarPredef")
        assignin('base','estadoApp','Se ha recibido la señal de inicio de la trayectoria definida');
        assignin('base','iniciarPredef',true);
        assignin('base','deltaEstado',true);
    end
    
end