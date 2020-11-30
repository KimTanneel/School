function [y,t,SoKhung] = TachThanhCacKhungTinHieu(y0,t0,Fs)
% ham tra ve tat cac khung tin hieu 20ms, voi cac khung dan xen nhau
% ------------------------------------------------------------------ 
% [y,t,SoKhung] = TachThanhCacKhungTinHieu(y0,t0,Fs) 
% y = ma tran MxN, voi M: so diem tung khung tin hieu 20ms, N: so khung 
% t = ma tran NxM, tuong ung la truc thoi gian cua tung khung 20ms 
% y0 = tin hieu dau vao 
% t0 = truc thoi gian cua y0 
% Fs = tan so lay mau cua y0
SoDiemTrong1Khung = floor(0.02*Fs); % so diem trong 1 khung tin hieu 20ms
L = length(y0); % xac dinh do dai cua y0;
y = []; % khoi tao ma tran rong (0x0) 
t = []; % khoi tao ma tran rong (0x0) 
a = 1; b = SoDiemTrong1Khung;  
% xac dinh vi tri dau va cuoi cua khung tin hieu 20ms dau tien 
while b<=L     
    y = horzcat(y,y0(a:b)); % noi theo so cot (tuc la tang so cot)     
    t = vertcat(t,t0(a:b)); % noi theo so hang (tuc la tang so hang)    
    a = b-floor(0.01*Fs); b = a+SoDiemTrong1Khung-1; 
    % xac dinh vi tri dau va cuoi cua khung tin hieu 20ms dau tien 
end
SoKhung = length(y(1,:)); % xac dinh so khung tin hieu  
end