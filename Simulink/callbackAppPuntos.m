function callbackAppPuntos(topic, msg)
    disp('Cargando puntos objetivo.');
    pause(0.3);
    disp('Cargando puntos objetivo..');
    pause(0.3);
    disp('Cargando puntos objetivo...');
    pause(0.3);
    %fprintf('MQTT callback topic "%s": "%s"\n', topic, msg)
    assignin('base','puntosLeidos',true);
    generarMatriz(msg);
end