function rutaGen = rutaPredef(ruta)
    if(ruta == 1)
        puntosObjetivo = zeros(2,4);
        puntoFinal = puntosObjetivo(1,1:3);
        yawFinal = 0;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',0);
    elseif(ruta == 2)
        puntosObjetivo = [0 0 -1 0 ; 0.55 0 -1 0; 1.1 0 -1 0.95*pi/2; 1.1 0.55 -1 pi/2; 1.1 1.1 -1 0.95*pi; 0.55 1.1 -1 pi ; 0 1.1 -1 pi ; 0 0.55 -1 pi ; 0 0 -1 pi];
        puntoFinal = [ 0 0 -1];
        yawFinal =  pi;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',1);        
    elseif(ruta == 3)
        puntosObjetivo = [0 0 -1 0 ; 0.5 -0.5 -1 -pi/4; 1 0.5 -1 pi/4; 1.5 -0.5 -1 -pi/4; 2 0.5 -1 pi/4];
        puntoFinal = [ 2 0.5 -1 ];
        yawFinal = pi/4;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',1);    
    elseif(ruta == 4)
        puntosObjetivo = [0 0 -1 0 ; 1.5 -0.5 -1 0; 0 -1 -1 0; 0 0 -1 0];
        puntoFinal = [0 0 -1];
        yawFinal = 0;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',1);   
    elseif(ruta == 5)
        puntosObjetivo = [0 0 -1 0 ; 1.5 0 -1 0];
        puntoFinal = [1.5 0 -1];
        yawFinal = 0;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',1);  
    elseif(ruta == 6)
        puntosObjetivo = [0 0 -1 0 ; 0 1.5 -1 0];
        puntoFinal = [0 1.5 -1];
        yawFinal = 0;
        assignin('base','puntosObjetivo', puntosObjetivo);
        assignin('base','puntoFinal', puntoFinal);
        assignin('base','yawFinal', yawFinal);
        assignin('base','modoOperacion',1);  
    end        
    rutaGen = true;
end