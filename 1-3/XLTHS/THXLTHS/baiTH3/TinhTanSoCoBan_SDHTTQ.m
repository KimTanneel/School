function [F0,Yttq,lag,lagmax] = TinhTanSoCoBan_SDHTTQ(TinHieu,Fs) 
% tinh tan so co ban % tra ve ham tu tuong quan voi cac do tre (lag) khac nhau,  
% tra ve do tre (lag) tai do dinh cao nhat thoa man 80<=F0<=400 
% ---------------------------------------------------------------- 
% F0 = tan so co ban ma thuat toan xac dinh duoc 
% Yttq = ham tu tuong quan cua tin hieu dau vao 
% lag = truc do tre (lag) cua Yttq 
% lagmax = do tre (lag) tai do dinh cao nhat thoa man 80<=F0<=400 
F0 = 0; lagmax = 0; % khoi tao cac gia tri ban dau 
[Yttq,lag] = HamTuTuongQuan(TinHieu); % xac dinh ham tu tuong quan 
% kiem tra tin hieu vao co tuan hoan khong? 
if Yttq(int32((1+length(lag))/2)) <10     
    return  
end
%----------------------------------------------------------------- 
% su dung noi suy cubic spline 
L = max(lag); 
lag2 = -L:0.1:L; 
Yttq = spline(lag,Yttq,lag2); 
lag = lag2; 
% ---------------------------------------------------------------- 
% tim kiem do tre co dinh lon nhat (Fs/400 < dotre <Fs/80) 
a = Fs/400; b = Fs/80; 
% xac dinh khoang do tre 
L = length(lag); 
ViTriBatDauDuyet = int32((1+L)/2);  
% xac dinh vi tri bat dau duyet (o giua cua do thi tu tuong quan) 
% xac dinh F0 
YttqMax = -1; 
for i = ViTriBatDauDuyet:L     
    if Yttq(i)>YttqMax && a<=lag2(i) && lag2(i)<=b      
        YttqMax = Yttq(i);    
        lagmax = i;     
        F0 = Fs/lag2(lagmax); % tinh tan so co ban F0    
    end
end
% ------------------------------------------------------------ 
end