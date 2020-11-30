clear;
[x,Fs] = audioread('studio_male.wav');
dt = 1/Fs;
subplot(211);
plot(x);
% Do dai cua tin hieu dau vao
tx = length(x)/16000;
% Do dai 1 khung la 20ms
SoKhungTinHieu =floor(tx/0.02);
%So Mau tren 1 khung
SoMauTrenKhung = 0.02*16000;

Rt = zeros(1,SoKhungTinHieu);
nl=0;nr=SoMauTrenKhung;
% do tre tren khung
lag = -SoMauTrenKhung:SoMauTrenKhung;
hamttqTaiKhungT = [];
F=zeros(1,SoKhungTinHieu);
for i=1:SoKhungTinHieu
    nl=SoMauTrenKhung*i-SoMauTrenKhung+1;
    nr=SoMauTrenKhung*i;
    hamttqTaiKhungT=[];
    tinhieu = x(nl:nr);
    
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
     hamttqTaiKhungT=y;
     count=0;
%           luu gia tri va vi tri cac dinh
            peaks= zeros(1,4);
            arrPeaksIndex=zeros(1,4);
            TTQ= hamttqTaiKhungT;
            CucDai= TTQ(1);
            for temp=2:length(hamttqTaiKhungT)-3
                if(TTQ(temp)<TTQ(temp+1)&& TTQ(temp+1)>TTQ(temp+2))
                    count=count+1;
                    peaks(count)=TTQ(temp+1);
                    arrPeaksIndex(count)=temp+1;
                end;   
                if(count==4)
                    break;
                end;
            end;
%             
            if(max(peaks)>0.25*CucDai && max(peaks)<CucDai)
%                 disp('HUU THANH');
%               Khoi tao 1 tong
                sum=0;
                for indexPeak=1:length(arrPeaksIndex)-1
                    sum=sum+(arrPeaksIndex(indexPeak+1)-arrPeaksIndex(indexPeak));
                        
                    
                end;
                sum=floor(sum/3);
                T0=sum/SoMauTrenKhung*0.02;
                F(i)=1/T0;
            else
                F(i)=0;
            end; 
     
     
     
         if(i==109)
            subplot(312);
            plot(tinhieu);
            title('Tin hieu');   
            subplot(313);
            plot(hamttqTaiKhungT);
             title('Ham tu tuong quan');
            disp(arrPeaksIndex);
            disp(F(i));
            disp(T0);
%           KHoi tao cac dinh  
            
        end;
% subplot(212);
% plot(F,'*');
end;

%     Test