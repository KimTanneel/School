clear all;
%%Cau a
Ts = 0.01;
Tsilence = 0.2;
[x1, Fs1] = audioread('studio_male.wav');
[frameArray1, frameQuantity1] = devideFrame(x1, Fs1, Ts);
%display(frameQuantity1);
[x2, Fs2] = audioread('lab_male.wav');
[frameArray2, frameQuantity2] = devideFrame(x2, Fs2, Ts);
%display(frameQuantity2);
[x3, Fs3] = audioread('studio_female.wav');
[frameArray3, frameQuantity3] = devideFrame(x3, Fs3, Ts);
%display(frameQuantity3);
[x4, Fs4] = audioread('studio_male.wav');
[frameArray4, frameQuantity4] = devideFrame(x4, Fs4, Ts);
%display(frameQuantity4);

%%Cau b
[frameEnergy1, E1] = Energy(x1, frameArray1, Fs1, Ts);
% subplot(2,1,1);
% plot(x1, 'color','blue');
% title('lab-female');
% hold on;
% plot(frameEnergy1, 'color','red');
% legend('x1', 'FrameEnergy1');


% frameEnergy2 = Energy(x2, frameArray2, Fs2, Ts);
% subplot(4,1,2);
% plot(x2,  'color','blue');
% title('lab-male');
% hold on;
% plot(frameEnergy2, 'color','red');
% legend('x2', 'FrameEnergy2');
% 
% frameEnergy3 = Energy(x3, frameArray3, Fs3, Ts);
% subplot(4,1,3);
% plot(x3, 'color','blue');
% title('phone-male');
% hold on;
% plot(frameEnergy3, 'color','red');
% legend('x3', 'FrameEnergy3');
% 
% frameEnergy4 = Energy(x4, frameArray4, Fs4, Ts);
% subplot(4,1,4);
% plot(x4, 'color','blue');
% title('phone-female');
% hold on;
% plot(frameEnergy4, 'color','red');
% legend('x4', 'FrameEnergy4');

%% Cau c
[Enorm1, thershold] = standardEnergy1(x1, frameEnergy1);
[borderline] = findSilence(thershold, frameEnergy1);

%%Function
function [frameArray, frameQuantity] = devideFrame(x, Fs, Ts) 
    Ns = Fs*Ts;                                        
    frameQuantity = fix(length(x)/(Ns));               
    count = 1;                                          
    for i = 1:frameQuantity
        for j=1:Ns
            frameArray(i,j) = x(count);
            count = count+1;
        end
    end
    for i = 1:(length(x) - Ns*frameQuantity)
        frameArray(frameQuantity+1, i) = x(count);
        count = count + 1;
    end
end

function [frameEnergy, E] =  Energy(x, frameArray, Fs, Ts)
    Ns = Fs*Ts;
    sum = 0;
    for i=1:ceil(length(x)/(Ns))
        for j=1:Ns
            sum = sum + frameArray(i,j)^2;
        end
        E(i) = sum; 
        sum = 0;
    end
    count = 1;
    for i=1:ceil(length(x)/(Ns))
        for j=1:Ns
            frameEnergy(count) = E(i);
            count = count+1;
        end
    end
end


 function [Enorm, thershold] = standardEnergy1(x, frameEnergy)
     Enorm = (frameEnergy - min(frameEnergy))/(max(frameEnergy) - min(frameEnergy));
     er = 0.01;
     thershold = er*(max(frameEnergy) - min(frameEnergy)) + min(frameEnergy);
     x1 = [0, length(x)];
     y1 = [thershold, thershold];
    %     subplot(2,1,2);
     plot(x);
     hold on;
     plot(frameEnergy);
     hold on;
     line(x1,y1,'Color', 'red');
end

function [borderline] = findSilence(thershold, frameEnergy)
    borderline = find(frameEnergy > thershold);
    L = zeros(1,length(borderline));
    L(1) = borderline(1);
    for i = 2 : length(borderline)
        if((borderline(i)-borderline(i-1)) > 3200)
            L(i) = borderline(i-1);
            L(i+1)=borderline(i);
        end
    end
    L(end) = borderline(end);
    F = find(L>0);
    
    for i=1:length(F)
        x = F(i);
        Xi = [L(x), L(x)];
        Yi = [-max(frameEnergy), max(frameEnergy)];
        line(Xi,Yi, 'color','black', 'Linestyle', '-.','LineWidth',1);
    end
end
    



