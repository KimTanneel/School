

nL=10;
nR=10;
n = -nL:nR;
un = 2*[zeros(1,nL) 1 ones(1,10)]
% n-3
subplot(2,2,1);
stem(n+3,un,'fill');
title('dich phai');
subplot(2,2,2);
% n+3
stem(n-3,un,'fill');
title('dich trai');

% -n-3
subplot(2,2,3);
stem(-n-3,un,'fill');
title('am so n k  -n-3')

% -n+3
subplot(2,2,4);
stem(-n+3,un,'fill');
title('am so n k -n+3');    

% 2*u[-n+3]



