% Khoi tao h(n)
h=[0 0 0.4 0.8 0.4 0 0];
nh= [-1:5];
% Khoi tao x(n)
x =[0 1 0.6 0 0];
nx = [-1:3];

lh=length(h); % do dai h = 7
lx= length(x);% do dai x = 5

y = conv(x,h);

ny1 = nx(1)+nh(1);
ny2 = nx(lx)+nh(lh);
ny= ny1:ny2;

stem(ny,y,'fill');

