% TCE = [515 420 370 250 135 120 60 20];
% nhdo = [29 23 27 25 20 23 23 27];
% ngay = 0:5:35;
% bar(ngay,nhdo);
% xlabel('Ngay');
% ylabel('Nhiet do (^{o}C)');
% h1 = gca;
% h2 = axes('Position',get(h1,'Position'));
% plot(days,TCE,'LineWidth',3)
% set(h2,'YAxisLocation','right','Color','none','XTickLabel',[])
% set(h2,'XLim',get(h1,'XLim'),'Layer','top')
% text(11,380,'Mat do','Rotation',--55,'FontSize',16)
% ylabel('TCE Mat do (PPM)')
% title('Xep chong do thi','FontSize',16)
% axis[xmin , xmax , ymin , ymax];
% x = 0:0.025:pi/2;
% plot(x,tan(x),'.');
% x = -pi:.1:pi;
% y = sin(x);
% plot(x,y)
% axis([-pi 2*pi -1.5 1.5]);
% 
% set(gca,'xtick',-pi:pi/2:pi);
% text(3*pi/4,sin(3*pi/4),'\leftarrowsin(t)=0.707','FontSize',12);
% set(gca,'xticklabel',{'-pi','-pi/2','0','pi/2','pi'});


N = 40;
num = [0.3 0.2 -0.3];
den = [1 0.9 -0.9];
h = impz(num,den,N);% N: s? l??ng m?u tính toán
stem(h);
x = randn(1,10);
y = conv(x,h);
subplot(311),stem(x);
subplot(312),stem(h);
subplot(313),stem(y);