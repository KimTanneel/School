function [y,t,Fs] = audioread2(file);
% doc tin hieu doc vao tu file tra ve 3 tham so y, t, Fs
%---------------------------------------
% [y,t,Fs] = audioread2(file) 
% y: tin hieu sau khi doc file
% t: truc thoi gian
% Fs: tan so lay mau 
[y,Fs] = audioread(file); % doc tin hieu doc vao tu file
max_value = max(abs(y)); % tim bien do lon nhat cua tin hieu y 
y = y/max_value; % quy bien do cua tin hieu cao nhat ve 1 
t = 1/Fs:1/Fs:(length(y)/Fs); % thoi gian cua y
end