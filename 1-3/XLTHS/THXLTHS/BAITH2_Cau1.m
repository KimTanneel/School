[x,Fs] = audioread('lab_female.wav');
info = audioinfo('lab_female.wav');
t = 0:(0.01):(info.Duration);
K = length(t);
y = x(1:152529);
n=1;
a= zeros(0);
for i = 1:1:K
    y = x(n:i*floor(152529/954)); 
    E = sum(y(1:length(y)).^2);
    a = [a,E];
    n = n+ floor(152529/954);
end
plot(a);
