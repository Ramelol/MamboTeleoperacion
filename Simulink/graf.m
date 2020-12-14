time = datX.time
X = datX.signals.values
plot(time, X,'Color',[0.3,0.3,0.3],'LineWidth',2)
grid minor
hold on
plot([0 17],[1 1],'LineStyle','--')
title("Control de Posición - x")
xlabel("Tiempo [s]")
ylabel("Posición [m]")
axis([0 17 0 1.2])