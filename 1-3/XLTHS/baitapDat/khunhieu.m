F0= 1000;

A = 0.1;
A1=1;
A2=10;
Fs = 16000;
Time = 2;


t = (0:1/Fs:Time);
s= 5*sin(2*pi*F0*t);
subplot(4, 1, 1);
plot(t(1:100), s(1:100));
title('s');
% sound(s, Fs);
% pause(Time + 0.5);

% noise = A*randn(1,length(s));
% xt0 = s + noise;
% subplot(4, 1, 2);
% plot(t(1:100), xt0(1:100));
% title('with noise A = 0.1');
% sound(xt0, Fs);
% pause(Time + 0.5);
 
noise=A1*randn(1,length(s));
xt1 = s + noise;
subplot(4, 1, 3);
plot(t(1:100), xt1(1:100));
title('with noise A = 1');
sound(xt1, Fs);
pause(Time + 0.5);

noise=A2*randn(1,length(s));
xt2 = s + noise;
subplot(4, 1, 4);
plot(t(1:100), xt2(1:100));
title('with noise A = 10');
sound(xt2, Fs);
pause(Time + 0.5);

figure;
M = [3 5 7 9];

for m = 1:length(M)
    b = 1/M(m)*ones(1, M(m));
    y = filter(b, 1, xt1);
    y = circshift(y', -(M(m) - 1) / 2)';
    rm = 0;
    for c = 1 : (length(y) - M(m))
        rm = rm + (y(c) - s(c)) * (y(c) - s(c));
    end
%     h = y - s;
    rmse = sqrt(sum(rm) / (length(y) - M(m)));

    if m == 1 || rmse < rmseMin
        rmseMin = rmse;
        mMin = m;
    end
    
    subplot(4, 1, m);
    plot(t(1:100),y(1:100));
    title(['with rmse = ', num2str(rmse)]);
end


sound(xt1, Fs);
pause(Time + 0.5);
b = 1/M(mMin)*ones(1, M(mMin));
y = filter(b, 1, xt1);
sound(y, Fs);