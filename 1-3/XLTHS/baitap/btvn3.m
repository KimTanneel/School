[x,Fs]=audioread('D:\VITA\School\1-3\XLTHS\baitap\Recording.wav');

x=x(:,1);
dt=1/Fs;
t=linspace(0, length(x)*dt, length(x)+1);
plot(t(1:end-1),x); 
xlabel('Seconds');
ylabel('Amplitude');
disp('Length in samples: ');
disp(length(x));
disp('Length in seconds: ');
disp(dt*length(x));

%sound(x,Fs);

%sound(x,Fs/2);

%sound(x,2*Fs);