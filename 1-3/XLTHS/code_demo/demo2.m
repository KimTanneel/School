a = [2 7 9 7; 3 1 5 6; 8 1 2 5]
% Ngh?ch ??o c?a ma tr?n a -->a'
% l?y các ph?n t? ? c?t 1 và 4 c?a m?ng a
%a(:,[1 4])
% reshape ( t? l? s? không thay ??i)
%reshape(a,2,6)
%a(:)
% thêm vào m?ng a dòng cu?i c?a a
%[a;a(end,:)]
%a(1:3,1:2)

% t?o vecto t? 0 ??n 1 b??c nh?y 0,1
x=0:0.1:1

% t?o vecto 20 ph?n t? cách ??u t? 1-->10
y=linspace(1, 10, 20)

