clear;
% [x,Fs] = audioread('studio_male.wav');
[x, Fs] = audioread('lab_female.wav');
dt = 1/Fs;
% Hieu chinh do dai l
l=(length(x)*dt-dt);
len_x=length(x);
%Ve tin hieu vao
t = 0:dt*100:l*100;
subplot(2,1,1);
plot(t,x);
title('studio-male');
b=[-0.5 0.5];
v=[0.703 2.967 3.276 4.450 4.819 5.695 6.017 7.273 8.05];
% v=[0, 0.689, 1.237,1.950,2.467,3.432,3.848,4.659,5.178,6.074,6.493,7.1,7.803,9.50];
%Ve bien tach khoang lang bang tay
for i=1:numel(v)
    a=[v(i)*100 v(i)*100];        
    line(a,b,'Color','red','LineStyle','--')
end
% cau 3 : ve bieu do nang luong
% so khung cua tin hieu dau vao
soKhungTinHieu = floor(v(end)/0.01); 
% phan doan tin hieu thanh cac khung cua so co do dai 10ms
n = 0:0.01:v(end); 
% so tin hieu trong mot khung
lk =  floor(len_x * 0.01 /v(end)); 
% tao mang voi lk  phan tu zero
energy = zeros(1, soKhungTinHieu);
% Binh phuong tin hieu dau vao x[n]^2?
y = x.*x;
nl = 1;
nr  = lk; 
for i=1:soKhungTinHieu
    energy(i) = sum(y(nl:nr)); %E[i] = xichma(sum(x[i]^2))
    % buoc nhay sau moi lan lap la lk
    nl = nl + lk;  
    nr = nr + lk;
end
% 0.03 0.25 0.28
subplot(212);
plot(energy);
hold on;
title('Bieu Do Nang Luong');
% Cau 4

	     energyMin = min(energy);
	     energyMax = max(energy);
	     X = (energy-energyMin)/(energyMax-energyMin);
         x1 = [0,length(X)];
         y1 = [0.025,0.025];
plot(t,x);
hold on;
plot(X);
hold on;
for i=1:numel(v) 
    a=[v(i)*100 v(i)*100];        
    line(a,b,'Color','red','LineStyle','--')
end
line(x1,y1,'Color','red');

