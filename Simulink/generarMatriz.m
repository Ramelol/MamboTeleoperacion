function generarMatriz(datosL)
    k = length(datosL{1});
    temp = datosL{1};
    for i=1:k
        if(double(temp(i)) == 40 || double(temp(i)) == 41)
            temp(i) = ' ';
        end
    end
    datosL = convertCharsToStrings(temp);
    datosArray = datosL.split();
    tam = length(datosArray)-2;
    puntosObjetivo = zeros((tam-4)/4,4);
    fil = 1;
    col = 1;
    for i=6:tam+1
        nums = datosArray(i).split(",");
        contDig = 0;
        pEnt = 0;
        pDec = 0;
        n = length(nums);
        for j=1:n
            if(nums(j) ~= "")
                contDig = contDig + 1;
                if(contDig == 1)
                    pEnt = double(nums(j));
                end
                if(contDig == 2)
                   pDec = double(nums(j));
                end
            end
        end
        num = pEnt + pDec/10;
        puntosObjetivo(fil,col) = num;
        col = col + 1;
        if(col == 5)
            col = 1;
            fil = fil + 1;
        end
    end 
    [f,c] = size(puntosObjetivo);
    rotMat = [ 0 1 0 ; 1 0 0 ; 0 0 -1];
    for i=1:f
        vecWR = puntosObjetivo(i,1:3);
        vecDR = rotMat*vecWR';
        puntosObjetivo(i,1:3) = vecDR';
    end
    puntosObjetivo(:,4) = puntosObjetivo(:,4)*pi/180; 
    puntoFinal = puntosObjetivo(f,1:3);
    yawFinal = puntosObjetivo(f,4);
    assignin('base','puntosObjetivo', puntosObjetivo);
    assignin('base','puntoFinal', puntoFinal);
    assignin('base','yawFinal', yawFinal);
    assignin('base','matrizGenerada', true);
end