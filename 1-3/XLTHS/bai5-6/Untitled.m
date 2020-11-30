clear all
load handel.mat
filename = 'handel.wav';
audiowrite(filename,y,Fs);
clear Fs;

[X,Fs] = audioload(filename);
sound(X,Fx);

%cau b)
%giam toc do lay mau di mot nua
k = 1;
a = zeros(length(X)/2);
for i =1:2:length(X)
    a(k)= X(i);
    k=k+1;
end
sound(a,Fs/2);