nL = 0;
nR = 20;
n = (nL: nR);
yi = 0;

 x1 = [1, zeros(1, nR)];
yn1 = zeros(1, length(n));
 ex = zeros(1, length(n));
 ex(1) = 0.9* yi + x1(1);
 yn1(1) = n(1)/(n(1)+1)* yi + x1(1);
 
 for  ii = 2: length(n)
     yn1(ii) = n(ii) * yn1(ii - 1)/(n(ii) + 1) + x1(ii);
     ex(ii) = 0.9 * ex(ii-1) + x1(ii);
 end
 
 %yn2 = filter(1, [1, -0.9], x1);
 subplot(2, 2, 1);
 stem(n, yn1, 'fill');
 xlabel('n');
 ylabel('y1[n]');
 title('yn1');
 
 
 subplot(2, 2, 2);
 stem(n, ex, 'fill');
  title('ex2');
  xlabel('n');
 ylabel('ex[n]');
 
 %---------------
 
 x2 = [zeros(1, 5), 1, zeros(1, 15)];
 yn1 = zeros(1, 21);
 yn1(1) = n(1)/(n(1)+1)* yi + x2(1);
 
 ex = zeros(1, length(n));
 ex(1) = 0.9* yi + x2(1);
 
 for  j = 2: length(n)
     yn1(j) = n(j) * yn1(j - 1)/(n(j) + 1) + x2(j);
     ex(j) = 0.9 * ex(j-1) + x2(j);
 end
 
 %yn4 = filter(1, [1, -0.9], x2);
 
 subplot(2, 2, 3);
 stem(n, yn1, 'fill');
 title('yn2');
 xlabel('n');
 ylabel('y3[n]');
 
 
 subplot(2, 2, 4);
  stem(n, ex, 'fill');
 title('ex2');
 xlabel('n');
 ylabel('ex[n]');
 

 
 