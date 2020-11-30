n = -20:1:20;
x = cos (0.1*n - pi/5);
subplot(2,1,1);
stem(n,x,'filled');
title('b) cos (0.1*n - pi/5)');

n = -10:1:20;
x = cos (0.1*pi*n - pi/5);
subplot(2,1,2);
stem(n,x,'filled');
title('c) cos (0.1*pi*n - pi/5)');
