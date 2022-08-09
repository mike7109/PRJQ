%clc; clear; close all;

figure;

plot(p_err_1);

grid on;
hold on;

line('XData', [0 20], 'YData', [2^-7 2^-7], 'Color','red','LineStyle','--');

title('Зависимость вероятности ошибки для CRC8');
xlabel('Кратность ошибки');
ylabel('Вероятность необнаружения');

legend('CRC8','0.0078');

figure;

plot(p_err_2);

grid on;
hold on;

line('XData', [0 20], 'YData', [2^-15 2^-15], 'Color','red','LineStyle','--');

title('Зависимость вероятности ошибки для CRC16');
xlabel('Кратность ошибки');
ylabel('Вероятность необнаружения');

legend('CRC16','3.0518e-05');

% size_packet = 64;
% numFrames = 1000000;
% frmError = 0;
% sumErrorCrc = 0;
% 
% poly = 'z8+z7+z6+z4+z2+1';
% crcgenerator = comm.CRCGenerator(poly);
% crcdetector = comm.CRCDetector(poly);
% 
% p_err_1 = zeros(20, 1);
% 
% for enbo = 1:20
%     for k = 1:numFrames
%         data = randi([0 1],size_packet,1);                 % Generate binary data
%         encData = crcgenerator(data);                   % Append CRC bits
%         numerrs = 0;
%         while 1
%             demodData = bsc(encData,enbo/size_packet);
%             [numerrs, ~] = biterr(demodData,encData);
%             if numerrs == enbo
%                 break
%             end
%         end
% 
%         [dataTx,frmError] = crcdetector(demodData);     % Detect CRC errors
%         sumErrorCrc = sumErrorCrc + frmError;
%       
%     end
% p_err_1(enbo) = (numFrames-sumErrorCrc)/numFrames;
% 
% sumErrorCrc = 0;
% end