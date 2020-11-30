function [Y_TuanHoan, t_TuanHoan] = TachVungTinHieuTheoBienDo(y,t,A) 
% tra ve vung tin hieu tuan hoan
% ------------------------------ 
% Y_TuanHoan = tin hieu trong vung tuan hoan 
% t_TuanHoan = truc thoi gian cua tin Y_TuanHoan 
% y = tin hieu dau vao % t = truc thoi gian cua y 
% A = bien do de xac dinh vung tuan hoan
dodai = length(y); % xac dinh so diem trong y
dau = 1;  
cuoi = dodai;      
% xac dinh vi tri dau cua vung tuan hoan 
for i = 1:dodai     
  if abs(y(i))>A         
    dau = i;          
    break;     
  end 
end
% --------------------------------------- 
% xac dinh vi tri cuoi cua vung tuan hoan 
for i = dodai:-1:1
    if abs(y(i))>A
        cuoi = i;
        break;
    end
end
% ---------------------------------------
Y_TuanHoan = y(dau:cuoi);
% cat vung tuan hoan gan cho Y_TuanHoan
t_TuanHoan = t(dau:cuoi);
% cat vung tuan hoan gan cho t_TuanHoan
end