[y1, fs] = audioread('lab_female.wav');
dt = 1/fs;
frame = linspace(0,0.0690,70);
l=(length(y1)*dt)-dt;
t = 0:frame:0.689;
%subplot(4,1,1)
plot(t,y1);
b=[-0.5 0.5];
v=[0, 0.689, 1.237,1.950,2.467,3.432,3.848,4.659,5.178,6.074,6.493,7.1,7.803,9.50];

% for i=1:numel(v) 
%     a=[v(i) v(i)];        
%     line(a,b,'Color','red','LineStyle','--')
% end
% 
% x = 0.1;y=0.2;
% n = linspace(x,y,20);
% x = 

