F0chuan = 123.7; %131.58; 
[y,t,Fs] = audioread2('/studio_female.wav');% doc tin hieu dau vao 
[y1,t1] = TachVungTinHieuTheoBienDo(y,t,0.3); % (BUOC 1) tach vung tin hieu theo bien do 
[y2,t2,SoKhung] = TachThanhCacKhungTinHieu(y1, t1, Fs); % (BUOC 2) tach vung tinh hieu thanh nhieu khung tin hieu 20ms 
[F0,tF0] = XacDinhDuongF0(y2,t2,SoKhung,Fs,F0chuan);% (BUOC 3 và B??C 4) xac dinh duong F0 
F0 = medfilt1(F0,7);% (BUOC 5) ket hop loc trung vi de lam tron duong F0  
[RMSE, F0tb] = XacDinhRMSE_TanSoF0(F0,F0chuan) % xac dinh RMSE va tan so co ban F0 trung binh   
% ve minh hoa 
subplot(3,1,1); plot(t,y);
hold on; 
plot(t1,y1); 
title('Tin hieu ban dau');
xlabel('Thoi gian (s)');
ylabel('Bien do'); 
subplot(3,1,2); 
plot(t1,y1); 
title('Tin hieu sau khi tach theo bien do'); 
xlabel('Thoi gian (s)');
ylabel('Bien do'); 
subplot(3,1,3); 
plot(tF0,F0,'*');
title('Duong bieu dien tan so co ban'); 
xlabel('Thoi gian (s)'); 
ylabel('F_0 (Hz)');