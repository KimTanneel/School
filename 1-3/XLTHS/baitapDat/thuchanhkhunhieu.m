% khoi tao cac bien
Fs = 16000;
time = 2;
F = 1000;
ts=1/Fs;
% khoi tao mang t voi tan so lay mau la Fs
n=(0:ts:time);

% ve tin hieu st
sn = 5*sin(2*pi*(F/Fs)*n);
subplot(4,1,1);
plot( sn(1:100));
title ('sn');

%Phat am thanh va dung 2 giay
% sound(st, Fs);


% random tin hieu nhieu tu 1->n voi n la tan so lay mau
dodaimau = length(sn);
noise = randn(1,dodaimau);

% ve noise
subplot(4,1,2);
plot(noise(1:100));

% x(t) = st(t) + noise(t)
xn = sn + noise;
% ve xt
subplot(4, 1, 3);
plot( xn(1:100));
title('xt');
% phat am thanh
% sound(xt,Fs);

M = [3,5,7,9];
M1 =3;
% for i =1:length(M)
%     mt1=ones(1,M(i));
%     num = 1/M(i)*mt1;
%     den =[1 zeros(1,M(i)-1)];
%     yt = filter(num,den,xt);
%     d=(M(i)-1)/2;
%     ydich= [y(d:end) zeros(1,d)];
% %     rmse
%     rmse =0;
%     for n =1 :length(t)
%         rmse = rmse+ sqrt((1/n)*(ydich-xt)*(ydich-xt));
%     end
%     subplot(4,2,i);
%     plot(rmse(1:100));
% end


