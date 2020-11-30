clear;
[x,Fs] = audioread('studio_female.wav');
dt = 1/Fs;
F0min=80;
F0max=350;
subplot(311);
plot(x);
% Do dai cua tin hieu dau vao
tx = length(x)/16000;
% Do dai 1 khung la 20ms
DoDaiKhung=0.02;
SoKhungTinHieu =floor(tx/DoDaiKhung);
%So Mau tren 1 khung
SoMauTrenKhung = DoDaiKhung*16000;

Rt = zeros(1,SoKhungTinHieu);
nl=0;nr=SoMauTrenKhung;
% do tre tren khung  
lag = -SoMauTrenKhung:SoMauTrenKhung;
hamttqTaiKhungT = [];
F=zeros(1,SoKhungTinHieu);
% Quet cac khung tin hieu+
Nguong=0.2 ;
for i=1:SoKhungTinHieu
    nl=SoMauTrenKhung*i-SoMauTrenKhung+1;
    nr=SoMauTrenKhung*i;
    hamttqTaiKhungT=[];
    tinhieu = x(nl:nr);
%    Ham tu tuong quan
     for to=1:SoMauTrenKhung
        tong =0;
        for j=1:SoMauTrenKhung   
            Rt=0;       
            if((j+to)<=SoMauTrenKhung)%neu lon hon so mau thi rt=0
            Rt = tinhieu(j+to); 
            end;
            tong =  tong +tinhieu(j).*Rt;%Rt= TongXichma (xi,x(j+to))
        end;  
    
        hamttqTaiKhungT=[hamttqTaiKhungT tong];
     end; 
     
            count=0;
%           luu vet cac gia tri va vi tri dinh
            peaks= zeros(1,8);
            arrPeaksIndex=zeros(1,8);
            TTQ= hamttqTaiKhungT;
%             Chuan hoaaaaa 
            
            maxGiatri = TTQ(1);
            TTQ=TTQ/maxGiatri;
            %Cuc dai tai vi tri x=0
            CucDai= TTQ(1);
            %F/350 & F/80
%                 
            mauMin = floor(1/F0max*SoMauTrenKhung/DoDaiKhung)+1;
            mauMax = floor(1/F0min*SoMauTrenKhung/DoDaiKhung);
            
            for temp=mauMin:mauMax
%               tim cac dinh thoa man Nguong =0.5
                if(TTQ(temp)<TTQ(temp+1)&& TTQ(temp+1)>TTQ(temp+2)&& (TTQ(temp+1)>Nguong*CucDai))
                    count=count+1;
                    peaks(count)=TTQ(temp+1);
                    arrPeaksIndex(count)=temp+1;
                end;   
                %max la 7 dinh
            
            
            end;
%           % neu huu thanh thi tim F0
            Maxpeaks=0;vitri=0;
            for p=1:length(peaks)
                if ( Maxpeaks<peaks(p))
                    vitri=arrPeaksIndex(p);
                    Maxpeaks=peaks(p);
                end;
            end;
            if(max(peaks)>Nguong*CucDai)
                if(Maxpeaks>Nguong*CucDai)
                    F(i)=1/(vitri*0.02/SoMauTrenKhung);
                end;
                
            else
            %vo thanh thi f=0;
                F(i)=0;
            end; 
%      Bat khung tin hieu tai vi tri 105
         if(i==59)
            subplot(312);
            
            plot(tinhieu);
            title('Tin hieu');   
            subplot(313);
            
            plot(TTQ);
             title('Ham tu tuong quan');
             maxPeak=0;posMaxPeak=0;
             line([vitri vitri],[-1 1]);
             line ([0 350],[0.5 0.5]);
             hold on;
            line ([mauMax mauMax], [-1 1],'color','yellow','LineStyle','--');
            line ([mauMin mauMin], [-1 1],'color','yellow','LineStyle','--');
            disp(arrPeaksIndex);
            disp(vitri);
            disp(i);
            disp(F(i));
            break;
%           KHoi tao cac dinh  
            
        end;
subplot(312);

plot(F,'.');
end;

%     Test