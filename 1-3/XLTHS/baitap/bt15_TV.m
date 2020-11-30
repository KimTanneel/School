
n=10;
% khoi tao hn
hn=[0 0 0.4 0.8 0.4 0 0];  
n_hn=-1:5; 

% khoi tao xn
xn=[0 1 0.6 0 0]; 
n_xn=-1:3; 

yn=conv(hn,xn);
n_yn=(-2:8); 

subplot(3,1,1);
stem(n_hn,hn,'fill'); 
title('h[n]');


subplot(3,1,2);
stem(n_xn,xn,'fill');
title('x[n]');


subplot(3,1,3);
stem(n_yn,yn,'fill'); 
title('y[n]');
