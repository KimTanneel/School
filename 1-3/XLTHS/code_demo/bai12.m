N = 40;
num = [0.3 0.2 -0.3];
den = [1 0.9 -0.9];
h = impz(num,den,N);% N: s? l??ng m?u tính toán
stem(h);
x = randn(1,10);
y = conv(x,h);
subplot(311),stem(x);
subplot(312),stem(h);
subplot(313),stem(y);