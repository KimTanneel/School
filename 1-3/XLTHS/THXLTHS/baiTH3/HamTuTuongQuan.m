function [y,lag] = HamTuTuongQuan(tinhieu) 
% ham tra ve ham tu tuong quan cua tin hieu dau vao (tinhieu)
% ------------------------------------------------------------
% [y,lag] = HamTuTuongQuan(tinhieu) 
% y = ham tu tuong quan cua tin hieu dau vao 
% lag = truc do tre (lag) cua y  
% tinhieu = tin hieu dau vao de tim ham tu tuong quan
dodai = length(tinhieu); % xac dinh do dai cua tinh hieu 
lag = -dodai:dodai; % xac dinh truc do tre (lag) cua y  
y = []; %khoi tao ma tran rong (0x0)
for k = lag     
    tong = 0; % khoi tao lai gia tri 0     
    for j = 1:dodai         
        B = 0; % vi tri khong xac dinh se cho bang 0         
        if 1<=j+k && j+k<=dodai             
            B = tinhieu(j+k);         
        end 
        tong = tong + tinhieu(j)*B;     
    end
    y = [y tong]; % them gia tri tinh duoc vao y 
end
end