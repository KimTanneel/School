% N so luong mau tinh toan
N=40;
num= [0.3 0.2 -0.3];
den=[1 0.9 -0.9 1];
h = impz(num,den,N);
subplot(4,1,1);
stem(h,'fill');


