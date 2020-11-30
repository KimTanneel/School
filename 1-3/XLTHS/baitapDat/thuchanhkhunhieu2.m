% khoi tao cac bien
Fs = 16000;
time = 2;
F = 1000;

% khoi tao mang t voi tan so lay mau la Fs
t=(0:1/Fs:time);

% ve tin hieu st
st = 5*sin(2*pi*F*t);
subplot(4,1,1);
plot( st(1:100));
title ('st');

%Phat am thanh va dung 2 giay
sound(st, Fs);


% random tin hieu nhieu tu 1->n voi n la tan so lay mau
n = length(t);
noise = randn(1,n);

% ve noise
subplot(4,1,2);
plot(noise(1:100));

% x(t) = st(t) + noise(t)
xt = st + noise;
% ve xt
subplot(4, 1, 3);
plot( xt(1:100));
title('xt');
% phat am thanh
sound(xt,Fs);
figure;
M = [3,5,7,9];
for i =1:length(M)

    mt1=ones(1,M(i));
% khoi tao he so cua x    
    num = 1/M(i)*mt1;
%  khoi tao he so cua y   
    den =[1 zeros(1,M(i)-1)];
% bo loc trung binh truot    
    yt = filter(num,den,xt);
% khoang cach lech pha
    d=(M(i)-1)/2;
% y sau khi da dich    
    ydich= [yt(d+1:end) zeros(1,d)];

    rmse = sqrt((sum((ydich-st).*(ydich-st)))/n);
    subplot(4,1,i);
    plot(ydich(1:100));
    hold on;
    plot(xt(1:100));
    title(M(i));
end


