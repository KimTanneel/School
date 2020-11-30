
% doc tin hieu tu file
[x,Fs]=audioread('studio_female.wav');
% do dai cua tin hieu x
lx = length(x);
% tham chieu den phan tu thu nhat
x=x(:,1);
dt=1/Fs;
t=linspace(0, length(x)*dt, length(x)+1);
subplot(311);
plot(t(1:end-1),x);
title('Do Thi Bien Chuan'); 
xlabel('Seconds');
ylabel('Amplitude');
disp('Length in samples: ');
disp(length(x));
disp('Length in seconds: ');
disp(dt*length(x));

    b=[-0.5 0.5];
v=[0.5735 0.705 0.807 1.330 1.415 1.590 1.630 2.148 2.477 3.235 3.308 3.678 3.723 3.921 3.982 4.248 4.920];
for i=1:numel(v)
    a=[v(i) v(i)];
    line(a,b,'color','red','LineStyle','--')
end
% cau 3 : ve bieu do nang luong 
soTinHieuCaKhung = floor(v(end)/0.01); % so tin hieu ca khung
n = 0:0.01:v(end); % phan doan tin hieu thanh cac khung cua so co do dai 10ms
lk =  floor(lx * 0.01 /v(end)) ; % so tin hieu trong mot khung
E = zeros(1, soTinHieuCaKhung);% tao mang voi lk  phan tu zero

y = x.*x;
nl = 1;
nr  = lk;
for i=1:soTinHieuCaKhung
    E(i) = sum(y(nl:nr));
    nl = nl + lk;
    nr = nr + lk;
end
subplot(312);
plot(E);title('Bieu Do Nang Luong');

%cau_4
A = zeros(1,soTinHieuCaKhung);
for i = 1:length(A)
    A(i) = log10(E(i));
end

Min = min(A);
Max  = max(A);
X_norm = zeros(1,soTinHieuCaKhung);
for i= 1:soTinHieuCaKhung
    X_norm(i) = (A(i) - Min) / (Max - Min);
end
subplot(313);
plot(X_norm);
hold on;
y= 0.6;
yline(y);

hold on;
