nR = 10;
nL = 10;
n=-nL:nR;
x = [zeros(1,nL),ones(1,nR+1)];
stem(n,x,'fill');

% nL = 10;
% nR = 10;
% n = -nL:nR;
% 
% x = [zeros(1,nL-1), -2, 4, -2, 2, -1, zeros(1,nR-3)]; 
% subplot(3,2,1)
% stem(n,x,'fill'); 
% title('x[n]');
% xlabel('Time (n)');
% ylabel('Amplitude');