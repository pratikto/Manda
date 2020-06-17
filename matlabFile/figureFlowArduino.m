
##Plot Sensor data and Sensor conversion data
figure('Name', 'Pressure Arduino Output');
axis(1) = subplot(3,1,[1 2]);
hold on;
plot(x,Flow, 'g');
plot(x,FlowSignalArdu, 'r');
xlim ([0 6364]);
##legend('Flow Sensor');
xlabel('Count');
ylabel('Flow');
title('Flow Sensor');
hold off;

axis(2) = subplot(3,1,3);
hold on;
plot(TidalVolumeArdu, 'r');
xlim ([0 6364]);
##legend('Flow Sensor Conversion');
xlabel('Count');
ylabel('Flow');
title('Tidal Volume');
hold off;