nL=10;
nR=10;
n=-nL:nR;
u=[zeros(1,nL),ones(1,nR+1)]
subplot(5,2,1)
stem(n,u,'fill')

%generate 2u[n-2]
u1=2*u;
subplot(5,2,2)
stem(n+2,u1,'fill')
title('cach1')
%generate 2u[n-2]
u1=2*u;
subplot(5,2,4   )
n1=[n,0,0]
n1(1:2)=[]
stem(n1,u1,'fill')
title('cach2')

% % generate 2u[n-7]
% u2 = 2*u;
% subplot(5,2,3)
% stem(n+7,u2,'fill')
% % generate 2u[-n]
% u3 = 2*u;
% subplot(5,2,4)
% stem(-n,u3,'fill')
% % generate 2u[4-n]
% u4 = 2*u;
% subplot(5,2,5)
% stem(4-n,u4,'fill')
% 
% y= u1-u2-u3+u4;
% subplot(5,2,6)
% stem(n,y,'fill');
