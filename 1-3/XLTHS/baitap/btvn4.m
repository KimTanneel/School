F0 = 12000; 
t = 5;
a = 1; 
p = 0;

Fs1 = 3*F0;
Ts1 = 1/Fs1;
n1=0:Ts1:t;
x1 = a*cos(2*pi*F0*n1*Ts1+p);
subplot(2,1,1);
stem(n1,x1,'fill');
title('x1[n]');
xlabel('Sample');
ylabel('Amplitude')

Fs2 = 1.5*F0;
Ts2 = 1/Fs2;
n2=0:Ts2:t;
x2 = a*cos(2*pi*F0*n2*Ts2+p);
subplot(2,1,2);
stem(n2,x2,'fill');
title('x2[n]');
xlabel('Sample');
ylabel('Amplitude')

sound(x1,Fs1);
%sound(x2,Fs2)

