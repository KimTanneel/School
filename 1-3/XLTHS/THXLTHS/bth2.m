	[x,Fs1] = audioread('studio_male.wav');
	n = Fs1/100; 				% S? m?u trong 10ms 
	size = floor(length(x)/n); 			% S? khung hình c?a tính hi?u
	      n = Fs1/100; 				% S? m?u trong 10ms	       size = floor(length(x)/n); 		% S? khung hình c?a tính hi?u
	      P=zeros(n,size); 			% T?o m?ng 2 chi?u 
	      for k=0:size-1
	           P(:,k+1)=x(1+n*k:n*(k+1));	% Gán giá tr? x vào khung
	       end
%  Câu b
	       E=zeros(1,size);	   % T?o m?ng E ch?a n?ng l??ng c?a t?ng khung
	       for i=1:size		   % Duy?t vòng l?p 
	       E(i) = sum(P(:,i).^2);	   %  G?n n?ng l??ng vào m?ng E
           end
	       %  V? ?? th? 
	       subplot(1,1,1);		    
	       plot(x);
	       hold on
	       plot(1:n:n*size,E);
%  Câu b
	       % CHu?n hóa n?ng l??ng v? [0,1]
	     E=log(E);
	     Emin = min(E);
	     Emax = max(E);
	     X = (E-Emin)/(Emax-Emin);
	     % TÌm giao ?i?m c?a ng??ng n?ng l??ng và ?? th? n?ng l??ng
	     B = [0.45, 0.5, 0.55];
	     figure(3);
	     for i = 1: 3
	            Inte=find(X>B(i));
	            F = zeros(1,length(Inte));
	            j = 2;
	            F(1) = Inte(1);
	            for j =2:length(Inte)-1
	                    if(Inte(j+1)-Inte(j)>20)
	                    F(j) = Inte(j);
	                    F(j+1)=Inte(j+1);
	                   end
	       end
	    % V? ?? th? 
	    F(end)=Inte(end);
	    F(length(X)) = length(X);
	    subplot(3,1,i);
	    plot(x);
	    hold on
	    lines = [B(i)*ones(1,length(x))];
	    plot(1:n:n*size,X);
	
	    % Ve các biên 
	    for l=1:length(F)
	         Xi = [F(l)*160 F(l)*160];
	         Yi = [-1 1];
	         line(Xi,Yi, 'color','black', 'Linestyle', '-.','LineWidth',1);
	    end
	    hold on;
	    plot(lines,'--','color','red');
	   end
