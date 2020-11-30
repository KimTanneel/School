% left & right bounds of time axis (in samples)
nL = 10;
nR = 10;
% create discrete-time vector
n = -nL:nR;
% processing
u4 = 2*[zeros(1,nL+2), 1, ones(1,nR-2)]; % generate 2u[n-2]
subplot(5,2,1)
stem(n,u4,'fill'); % plot 2u[n-2]
title('2u[n-2]');
xlabel('Time (n)');
ylabel('Amplitude');

u5 = 2*[zeros(1,nL+7), 1, ones(1,nR-7)]; % generate 2u[n-7]
subplot(5,2,3)
stem(n,u5,'fill'); % plot 2u[n-7]
title('2u[n-7]');
xlabel('Time (n)');
ylabel('Amplitude');

u6 = 2*[ones(1,nL), 1, zeros(1,nR)]; % generate 2u[-n]
subplot(5,2,5)
stem(n,u6,'fill'); % plot 2u[-n]
title('2u[-n]');
xlabel('Time (n)');
ylabel('Amplitude');

u7 = 2*[ones(1,nL+4), 1, zeros(1,nR-4)]; % generate 2u[4-n]
subplot(5,2,7)
stem(n,u7,'fill'); % plot 2u[4-n]
title('2u[4-n]');
xlabel('Time (n)');
ylabel('Amplitude');

y = u4-u5-u6+u7; % generate y[n]
subplot(5,2,2)
stem(n,y,'fill'); % plot y[n]
title('y[n]');
xlabel('Time (n)');
ylabel('Amplitude');

a = 2-3*y; % generate 2-3y[n]
subplot(5,2,4)
stem(n,a,'fill'); % plot 2-3y[n]
title('a) 2-3y[n]');
xlabel('Time (n)');
ylabel('Amplitude');

b = 3*y; % generate 3y[n-2]
subplot(5,2,6)
stem(n-2,b,'fill'); % plot 3y[n-2]
title('b) 3y[n-2]');
xlabel('Time (n)');
ylabel('Amplitude');

c = 2-2*y; % generate 2-2y[n-2]
subplot(5,2,8)
stem(n+2,c,'fill'); % plot 2-2y[n-2]
title('c) 2-2y[n-2]');
xlabel('Time (n)');
ylabel('Amplitude');

d = y; 
subplot(5,2,9)
stem(-n,d,'fill');
title('d) y[-n]');
xlabel('Time (n)');
ylabel('Amplitude');


