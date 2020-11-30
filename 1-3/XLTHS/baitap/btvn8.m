% P0208: Plot the 5-point moving average filter
% y[n] = 1/5*(x[n]+x[n-1]+x[n-2]+x[n-3]+x[n-4]);
close all; clc
n = 0:20;
x = [ones(1,10), 1 , zeros(1,10)];
a = [1];
b= [ones(1,5)/5];
hn = impz(b,a,x);
stem(n,hn);
title('a)')
xlabel('n')
ylabel('Amplitude')