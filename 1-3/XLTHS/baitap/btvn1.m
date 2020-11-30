nL = 10;
nR = 10;
n = -nL:nR;

x = [zeros(1,nL-1), -2, 4, -2, 2, -1, zeros(1,nR-3)]; 
subplot(3,2,1)
stem(n,x,'fill');   
title('x[n]');
xlabel('Time (n)');
ylabel('Amplitude');

a = 3*x;
subplot(3,2,2)
stem(-n-1,a,'fill'); 
title('a) 3x[-n-1]');
xlabel('Time (n)');
ylabel('Amplitude');

b = 3*x-1;
subplot(3,2,4)
stem(2*n,b,'fill'); 
title('b) x[2n]-1');
xlabel('Time (n)');
ylabel('Amplitude');

c = -x + 2;
subplot(3,2,6)
stem(n,c,'fill'); 
title('c) -x[n]+2');
xlabel('Time (n)');
ylabel('Amplitude');
