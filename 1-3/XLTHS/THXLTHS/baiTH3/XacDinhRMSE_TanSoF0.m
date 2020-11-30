function [RMSE,F0tb] = XacDinhRMSE_TanSoF0(F0,F0chuan) 
% tra ve RMSE cua duong tan so co ban F0 
% --------------------------------------- 
% [RMSE,F0tb] = XacDinhRMSE_TanSoF0(F0,F0chuan) 
% RMSE = sai so toan phuong trung binh 
% F0tb = Tan so co ban trung binh 
% F0 = duong tan so co ban 
% F0chuan = tan so co ban chuan do thu cong 
L = 1:length(F0); % xac dinh do dai duong F0 
Sum = 0; % khoi tao gia tri bang 0 
Dem=0; % bien dem so luong F0 xac dinh 
F0tb=0; 
for i=L     
    if (F0(i)>0)         
        Dem = Dem+1;         
        Sum = Sum + (F0chuan-F0(i))^2; % tong cac binh phuong sai
        F0tb = F0tb+F0(i);    
    end
end
RMSE = sqrt(Sum/Dem); % tinh sai so toan phuong trung binh RMSE 
F0tb = F0tb/Dem;% tinh tan so co ban trung binh
end