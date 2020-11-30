% tao he thong 1
N = 6;
num1=[2 -0.5 0 0.5];
den1=[1 -0.1 0 0];
h1=impz(num1,den1,N);
% 

num2=[0.3 0 0.2];
den2=[1 0 0.1];
h2 = impz(num2,den2,N);

% Tao tin hieu vao ngau nhien
x=randn(1,5);

% kiem tra tinh giao hoan
y11= conv(x,h1);
y1 = conv(y11,h2);
subplot(2,2,1);
stem(y1,'fill');

y21= conv(x,h2);
y2 = conv(y21,h1);
subplot(2,2,2);
stem(y2,'fill')

%kiem tra tinh ket hop

% cung so chieu moi cong duoc 


