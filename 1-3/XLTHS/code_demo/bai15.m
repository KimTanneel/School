x=[0 1 0.6 0 0];
nx=-1:3;
subplot(311); 
stem(nx,x);
title('x(n)')

h=[0 0 0.4 0.8 0.4 0 0];
nh=-1:5;
subplot(312); 
stem(nh,h); 
title('h(n)')

y=conv(x,h);
ny1=nx(1) + nh(1);
ny2=nx(length(x)) + nh(length(h));
ny=[ny1:ny2];
subplot(313);
stem(ny,y); 
title('y(n)')