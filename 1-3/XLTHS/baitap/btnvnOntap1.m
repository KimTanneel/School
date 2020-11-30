a = 10;
phi = pi;
% omega = linspace(-pi,pi,10);
omega = pi/9;
t=linspace(0,100,100);

x=zeros(1,10);

for i=1:length(omega)
%    x= a*sin(omega(i)*2*pi*t+phi);
    x = a*sin(omega+i*2*pi)*t+phi;
    
   subplot(5,2,i);
  
   plot(t,x);
   title(num2str(omega(i)));
%    x=zeros(1,10);
end