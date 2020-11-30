function [F0,tF0,RMSE] = XacDinhDuongF0(y2,t2,SoKhung,Fs,F0chuan) 
% xac dinh duong F0 tu tat ca cac khung tin hieu 30ms 
% tra ve sai so toan phuong trung binh RMSE 
% -------------------------------------------------------------- 
% F0 = duong tan so co ban F0 
% tF0 = truc cua F0 tren do thi 
% RMSE = sai so toan phuong trung binh
% y2 = ma tran MxN, chua tat cac cac khung tin hieu 20ms 
% t2 = ma tran NxM, chua truc thoi gian tung khung tin hieu 20ms 
% Fs = tan so lay mau 
% F0chuan = tan so co ban F0 chuan do thu cong
tF0 = []; % khoi tao ma tran rong (0x0) 
F0 = []; % khoi tao ma tran rong (0x0)      
for i = 1:SoKhung         
    [F00,Yttq,lag,lagmax] = TinhTanSoCoBan_SDHTTQ(y2(:,i),Fs);          
    % tinh tan so co ban cua tung khung tin hieu 20ms        
    F0 = [F0 F00]; % them tan so co ban tinh duoc vao ma tran         
    tF0 = [tF0 t2(i,floor((1+length(t2(i,:)))/2))];          
    % xac dinh truc F0 tren do thi  
end 
end