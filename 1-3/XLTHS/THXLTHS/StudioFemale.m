
[x,Fs] = audioread('studio_female.wav');
info = audioinfo('studio_female.wav');

%cau_1&2
t_x = 0:(1/Fs):info.Duration;
t = 0:(0.01):(info.Duration); 
t = [t, t(end) + mod(info.Duration,0.01)];
K = length(t)-1;
n=1;

for i = 1:1:K
    if (i==K)
        y = x(n:info.TotalSamples);
        E = sum(y(1:length(y)).^2);
        a (i) = E;
        break;
    end
    y = x(n:i*(Fs*0.01)); 
    E = sum(y(1:length(y)).^2);
    a(i) = E;
    n = n+ Fs*0.01;
end
subplot(311);
plot(t(2:end),a);
title('Nang luong ngan han');

%cau 3
subplot(312);
plot(t_x(2:end),x);
hold on;
xline(0.5736);
xline(2.148);
xline(2.477);
xline(4.248);
title('bien chuan');
boundary = [0.5736 2.148 2.477 4.248];

%cau_4
for i = 1: length(a)
    A(i) = log10(a(i));
end

Min = min(A);
Max  = max(A);

for i= 1:length(A)
    X_norm(i) = (A(i) - Min) / (Max - Min);
end
subplot(313);
plot(t(2:end),X_norm);
hold on;
y= 0.6;
yline(y);
hold on;

silence = X_norm < y;
boundary_2 = zeros(0);
point = 0;
for i=1:length(silence)-1
   if (silence(i)==1 && silence(i+1)==0) 
        if ((i - point)/100 > 0.2 )
            xline(i/100);
            xline(point/100);
            boundary_2 = [boundary_2 ,point/100 , i/100];
        end
    elseif (silence(i)==1 && i == length(silence)-1)
            xline(point/100);
            boundary_2 = [boundary_2 ,point/100 ];
            break;
    end
    if (silence(i)==0 && silence(i+1)==1)
        point = i+1;
    end
end
title('Bien tim bang thuat toan');
%sai so
delta =abs(boundary_2(2:end) - boundary);