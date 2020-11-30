[y1, fs] = audioread('lab_female.wav');
dt = 1/fs;
l=(length(y1)*dt)-dt;
t = 0:dt:l;
%subplot(4,1,1)
subplot(2,1,1)
plot(t,y1);
b=[-0.5 0.5];
v=[0, 0.689, 1.237,1.950,2.467,3.432,3.848,4.659,5.178,6.074,6.493,7.1,7.803,9.50];

for i=1:numel(v) 
    a=[v(i) v(i)];        
    line(a,b,'Color','red','LineStyle','--')
end

frame = 0:0.1:l;
for x=1:numel(frame) 
    c=[frame(x) frame(x)];        
    line(c,b,'Color','green','LineStyle','--')
end
% for i=1:numel(v)
    % 9.53 s --> 152529
    % 0.01 s --> 160,1      
%     mau1khung = 160 ;
%     n = linspace(8000,8159,160);
%     E = y1.*y1;
n = 0:0.01:9.5;
lk = 160;
E = zeros(1,950);

for i=1:950
    if i == 1
        for j=1:160
            E(i) = E(i) + x(j)*x(j);
        end
    else
        for j= ((i-1)*160):(i*160)
            E(i) = E(i) + x(j)*x(j);
        end
    end
end
subplot(212);title('Bieu Do Nang Luong');
plot(E);
