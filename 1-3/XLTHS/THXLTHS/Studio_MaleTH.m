clear;
[x,Fs] = audioread('studio_female.wav');
dt = 1/Fs;
% Hieu chinh do dai l
l=(length(x)*dt-dt);
len_x=length(x);
%Ve tin hieu vao
t = 0:dt*100:l*100;
subplot(2,1,1);
plot(t,x);
title('studio-female');
b=[-0.5 0.5];
v=[0.568 0.748 0.818 1.323 1.425 2.147 2.482 3.917 3.985 4.26 4.897];
% v=[0.703 2.967 3.276 4.450 4.819 5.695 6.017 7.2r73 8.05];
% 
% Ve bien tach khoang lang bang tay
for i=1:numel(v)
    a=[v(i)*100 v(i)*100];        
    line(a,b,'Color','red','LineStyle','--')
end

% cau 3 : ve bieu do nang luong
% so khung cua tin hieu dau vao
soKhungTinHieu = floor(len_x/Fs/0.01); 
% phan doan tin hieu thanh cac khung cua so co
% do dai 10ms
n = 0:0.01:v(end); 
% so tin hieu trong mot khung
lk =  floor(len_x * 0.01 /(len_x/16000)); 
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
% plot(energy);
% hold on;
title('Bieu Do Nang Luong');
% Cau 4
        energy=log(energy);
	     energyMin = min(energy);
	     energyMax = max(energy);
	     X = (energy-energyMin)/(energyMax-energyMin);
         x1 = [0,length(X)];
         y1 = [0.6,0.6];
% plot(t,x);
% hold on;
% X=log(X);

plot(X);
hold on;
% for i=1:numel(v) 
%     a=[v(i)*100 v(i)*100];        
%     line(a,b,'Color','red','LineStyle','--')
% end
% NguongNLChuan =0.55*(energyMax-energyMin)+energyMin;
NguongNLChuan=0.6;
line(x1,y1,'Color','red');
% X=log(X);
border = find(X>NguongNLChuan);
L =  zeros(1,length(border));
L(1)=border(1);
L(length(border))=border(length(border));
% boder(end)=boder(e)
for i = 2 : length(border)
        if((border(i)-border(i-1)) >=20)
            L(i) = border(i-1);
            L(i+1)=border(i);
        end
end

for i=1:length(L)
        if(L(i)>0)
        Xi = [L(i), L(i)];
        Yi = [min(X), max(X)];
        line(Xi,Yi, 'color','red', 'Linestyle', '--');
        end;
end

% Tao E trung binh  

% DoLechChuan = sqrt(sum((energy - mean(energy).*(energy - mean(energy)))/length(energy)));
% DoLechChuan = sqrt(sum((energy-mean(energy)).*(energy-mean(energy)))/length(energy));
% Xnorm = (energy-mean(energy))/DoLechChuan;
% plot(Xnorm);

