
n=1:10; 

hsx1=[2 -0.5 0 0.5]; 
hsy1=[1 -0.1 0 0];    
h1=impz(hsx1,hsy1,n);  

hsx2=[0.3 0 0.2 0]; 
hsy2=[1 0 0.1 0];    
h2=impz(hsx2,hsy2,n);  

x=linspace(1,5,10); 
%  x*(h1*h2)
H_0=conv(h1,h2);
y_0=conv(x,H_0);
subplot(3,1,1);
stem(y_0,'fill');
title('y(n) = x(n) * (h1(n)*h2(n))');

%  (x*h1)*h2
H_1=conv(x,h1);
y_1=conv(H_1,h2);
subplot(3,1,2);
stem(y_1,'fill');
title('y(n) = (x(n)*h1(n)) * h2(n)');

%  (x*h2)*h1
H_2=conv(x,h2);
y_2=conv(H_2,h1);
subplot(3,1,3);
stem(y_2,'fill');
title('y(n) = (x(n)*h2(n)) * h1(n)');
