clear;
clf;
[y,Fs] = audioread('../Tin Hieu Mau/studio_male.wav');
% sound(y,Fs);
%% Cac bien can dung
dt = 1/Fs; %Chu kì lay mau
l=(length(y)*dt)-dt; %Do dai theo giay cua file
t = 0:dt:l; %Vecto mien thoi gian cua file
frameTime=0.02;% Thoi gian 1 khung =20ms
n = ceil(l/frameTime);%So khung
lengthFrame=(l*Fs)/ n; %So mau trong 1 khung
threshold=0.1; % Nguong
%% Ve tin hieu
subplot(2,1,1);
plot(t,y);
title('Signal');
ylabel('Amplitude');
xlabel('Time(s)');
%% Tim F0 
nL1 = 1;
nR1 = lengthFrame;
% Tan so tieng noi trong khoang tu 70Hz - 400Hz
% -> T0 thuoc khoang : T0_speech
T0_speech = round(Fs/400):round(Fs/70);
for i=0:n-1
    nL = round(nL1 + i * lengthFrame);
    nR = round(nR1 + i * lengthFrame);
    % Bo loc Gaussian loc cao do ao (virtual pitch)
    w = gausswin(10);
    x=y(nL:nR);
    x = conv(x, w);
    %Ham tu tuong quan
    r=0;
    for lags = 0:lengthFrame
        x1 = vertcat(x,zeros(lags,1)); %Tin hieu goc
        x2 = vertcat(zeros(lags,1), x); %Tín hieu tre 
        r(lags+1)=sum(x1.*x2);
    end
    peak=findpeaks(r(T0_speech)); % Tim cac dinh trong khoang tieng noi
    if max(peak)>threshold
        IDmaxPeak = find(r == max(peak));
        T0=(IDmaxPeak/lengthFrame)*frameTime;
        F0(i+1)=1/T0;        
    end
end
F0 = medfilt1(F0,7); % Lam tron(smooth) do thi bang bo loc trung vi he so N=7
F0_plot = 0;
F0=[F0 zeros(1,n-length(F0))];
for i=1:n
        F0_plot(round(i*lengthFrame)) = F0(i);
end
%% Ve Do thi cao do (pitch)
t_F0 = 0:dt:l-dt;
subplot(2,1,2);
plot(t_F0,F0_plot,'.');
title('Pitch of Signal');
ylabel('Frequency(Hz)');
xlabel('Time(s)');