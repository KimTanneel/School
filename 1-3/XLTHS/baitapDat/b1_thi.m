h1=[2 -1 3]
n1=[0 1 2 ]
subplot(2,2,1)
stem(n1,h1,'fill')
title('HELLO');
h2=[-2 1 0]
n2=[0 1 2]
subplot(2,2,2)
stem(n2,h2,'fill');

h12 =h1+h2;

n3=[0 1 2]
x=[1 1 0]
subplot(2,2,3)
yn = conv(x,h12)
stem(yn,'fill')