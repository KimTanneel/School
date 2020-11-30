nL=10;
nR=10;
n=-nL:nR;
un (n>=0) =1;
un (n<0) = 0;
stem(n,un,'fill');
title('Bai2.1');
