nL=10;
nR=10;
n = -nL:nR;
un = [zeros(1,nL) 1 ones(1,10)]
% un (n>=0) =1;
% un (n<0) = 0;
% (1/2)^n*u[n]

a=1/2;
x1=(a.^n.*un);
subplot(2,1,1);
stem(n,x1,'fill');
title('(1/2)^n*n[n]');
