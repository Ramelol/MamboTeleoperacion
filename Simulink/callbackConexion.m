function callbackConexion(topic, msg)
    %fprintf('MQTT callback topic "%s": "%s"\n', topic, msg)
    if(msg=="AppConectada")
        assignin('base','conApp',true);
    else
        assignin('base','conApp',false);
    end
end