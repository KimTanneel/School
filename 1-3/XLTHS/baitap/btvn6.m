load('handel.mat')

n = 1:length(y);
%sound(y,Fs);

y2 = mod(n,2) == 1;
%sound(y(y2),Fs/2)

y4 = mod(n,4) == 1;
%sound(y(y4),Fs/4)      

audiowrite('6d.wav',y(y4),Fs/4)