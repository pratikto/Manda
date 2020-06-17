
figure('Name', "Flow Peak Detection");
axis(1) = subplot(2,2,1); 
hold on;
x = 1:length(Flow); ix = FlowLag+1:length(Flow);
area(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'FaceColor',[0.9 0.9 0.9],'EdgeColor','none');
area(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'FaceColor',[1 1 1],'EdgeColor','none');
plot(x(ix),FlowAvg(ix),'LineWidth',1,'Color','cyan','LineWidth',1.5);
plot(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
plot(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
plot(1:length(Flow),Flow,'b');
xlabel('Count');
ylabel('Flow');
axis(3) = subplot(2,2,3);
hold on;
stairs(FlowSignals*5,'r','LineWidth',1.5); 
stairs(_FlowSignals*5,'y','LineWidth',1.5); 
##legend("FlowSignals", "_FlowSignals");
xlabel('Count');
ylabel('Flow');
axis(4) = subplot(2,2,[2,4]); 
hold on;
x = 1:length(Flow); ix = FlowLag+1:length(Flow);
##area(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'FaceColor',[0.9 0.9 0.9],'EdgeColor','none');
##area(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'FaceColor',[1 1 1],'EdgeColor','none');
##plot(x(ix),FlowAvg(ix),'LineWidth',1,'Color','cyan','LineWidth',1.5);
##plot(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
##plot(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
plot(1:length(Flow),Flow,'b');
stairs(_FlowSignals*5,'y','LineWidth',1.5);
stairs(FlowSignals*5,'r','LineWidth',1.5); 
xlabel('Count');
ylabel('Flow');

figure('Name', "Flow Peak Detection");
##subplot(2,1,1); 
hold on;
x = 1:length(Flow); ix = FlowLag+1:length(Flow);
area(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'FaceColor',[0.9 0.9 0.9],'EdgeColor','none');
area(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'FaceColor',[1 1 1],'EdgeColor','none');
plot(x(ix),FlowAvg(ix),'LineWidth',1,'Color','cyan','LineWidth',1.5);
plot(x(ix),FlowAvg(ix)+FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
plot(x(ix),FlowAvg(ix)-FlowThreshold*FlowDev(ix),'LineWidth',1,'Color','green','LineWidth',1.5);
plot(1:length(Flow),Flow,'b');
##subplot(2,1,2);
stairs(_FlowSignals*5,'y','LineWidth',1.5); 
stairs(FlowSignals*5,'r','LineWidth',1.5); 
##ylim([-1.5 1.5]);
