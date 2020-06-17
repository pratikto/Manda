%% Start of script
addpath('peakDetection');           % include library
close all;                          % close all figures
clear;                              % clear all variables
clc;                                % clear the command terminal

##import sensor data
FlowSensor = csvread ("FlowSensor.csv");
PressureSensor = csvread ("PressureSensor.csv");

#import arduino data
FlowSignalArdu      = dlmread("FlowArdu.csv", ",", [0 0 6364 0]);
TidalVolumeArdu     = dlmread("FlowArdu.csv", ",", [0 1 6364 1]);
PressureSignalArdu  = dlmread("PressureArdu.csv", ",", [0 0 1358 0]);
PPeakArdu           = dlmread("PressureArdu.csv", ",", [0 1 1358 1]);
PAverageArdu        = dlmread("PressureArdu.csv", ",", [0 2 1358 2]);
PPEPArdu            = dlmread("PressureArdu.csv", ",", [0 3 1358 3]);
BpmArdu             = dlmread("PressureArdu.csv", ",", [0 4 1358 4]);

##scale Flow sensor data to 0.0 - 5.0
Flow = zeros(length(FlowSensor),1);
tFlow = zeros(length(FlowSensor),1);
maxFlowSensor = max(FlowSensor);
minFlowSensor = min(FlowSensor);
for i = 1:length(FlowSensor)
  Flow(i) = (FlowSensor(i)-minFlowSensor)/(maxFlowSensor-minFlowSensor)*5;
  tFlow(i) = i/30;
endfor

##scale Pressure sensor data to 0.0 - 5.0
Pressure = zeros(length(PressureSensor),1);
tPressure = zeros(length(PressureSensor),1);
maxPressureSensor = max(PressureSensor);
minPressureSensor = min(PressureSensor);
for i = 1:length(PressureSensor)
  Pressure(i) = (PressureSensor(i)-minPressureSensor)/(maxPressureSensor-minPressureSensor)*5;
  tPressure(i) = i/30;
endfor

##Export sensor conversion
dlmwrite ('flow.dat', Flow, "delimiter", ",", "newline", ",\n")
dlmwrite ('pressure.dat', Pressure, "delimiter", ",", "newline", ",\n")
##csvwrite("Flow.csv", Flow);
##csvwrite("Pressure.csv", Pressure);

% Peak detection algorithm Settings
FlowLag = 100;
FlowThreshold = 3.8;
FlowInfluence = 0.01;
PressureLag = 10;
PressureThreshold = 4;
PressureInfluence = 0.1;

% Detect peak flow data
[_FlowSignals,FlowAvg,FlowDev] = PeakDetection(Flow,FlowLag,FlowThreshold,FlowInfluence);

FlowSignals = zeros(length(_FlowSignals),1);
FlowSignals = _FlowSignals;
PastState = 0;
CurrentState = 0;
PastCount = 0;
CurrentCount = 0;
for i = 2:length(FlowSignals)
  if ((FlowSignals(i-1) == 1) && (FlowSignals(i) == 0))
    CurrentState = 1;
    CurrentCount = i;
  elseif ((FlowSignals(i-1) == -1) && (FlowSignals(i) == 0))
    CurrentState = -1;
    CurrentCount = i;
  end
  if FlowSignals(i-1) == FlowSignals(i)
    FlowSignals(i-1) = 0;
  end;
##  if CurrentState == PastState
##    FlowSignals(PastCount) = 0;
##  end
  PastState = CurrentState;
  PastCount = CurrentCount;
endfor;

% Detect peak Pressure data
[_PressureSignals,PressureAvg,PressureDev] = PeakDetection(Pressure,PressureLag,PressureThreshold,PressureInfluence);

PressureSignals = zeros(length(_PressureSignals),1);
PressureSignals = zeros(length(_PressureSignals),1);
PressureSignals = _PressureSignals;
PastState = 0;
CurrentState = 0;
for i = 2:length(PressureSignals)
  if ((PressureSignals(i-1) == 1) && (PressureSignals(i) == 0))
    CurrentState = 1;
  elseif ((PressureSignals(i-1) == -1) && (PressureSignals(i) == 0))
    CurrentState = -1;
  end
##  if ((PressureSignals(i-1) == PressureSignals(i)) || (CurrentState == PastState))
  if PressureSignals(i-1) == PressureSignals(i)
    PressureSignals(i-1) = 0;
  end;
  PastState = CurrentState;
endfor;

#call figure