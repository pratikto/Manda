
##Plot Sensor data and Sensor conversion data
figure('Name', 'Pressure Arduino Output');
subplot(3,1,[1 2]);
hold on;
plot(Pressure, 'g');
plot(PressureSignalArdu, 'r');
xlim ([0 1358]);
##legend('Pressure Sensor');
xlabel('Count');
ylabel('Pressure');
title('Pressure Sensor');
hold off;

subplot(3,1,3);
hold on;
plot(PPeakArdu, 'b');
plot(PAverageArdu, 'g');
plot(PPEPArdu, 'r');
xlim ([0 1358]);
legend('PPeak', 'PAverage', 'PPEP');
xlabel('Count');
ylabel('Pressure');
title('Pressure Sensor Conversion');
hold off;