clc; clear; close all;

num_bit = 2^5;
numFrames = 2;
sum_err = 0;
num_exp = 100;
zz = 1;
typeCrc = 1;
maxFrames = 102;


% while numFrames <= maxFrames
%     
%     for kk = 1:num_exp
%         sum_err = sum_err + happay_fun_try(num_bit, numFrames, typeCrc);
%     end
%     
%     p_err(zz) = sum_err/num_exp;
%     step_vec(1, zz) = numFrames;
%     numFrames = numFrames + 10;
%     zz = zz + 1;
%     sum_err = 0;
% end
% 
% n_max = 2^8;
% p1 = 1 - exp(-(step_vec.*(step_vec-1))/(2*n_max));
% 
% figure;
% plot(step_vec, p_err * 100, '-', 'LineWidth', 2);
% grid on;
% hold on;
% plot(step_vec, p1 * 100,  '-', 'LineWidth', 2);
% 
% title('Расчет криптостойкости - CRC8', 'FontSize', 12);
% xlabel('Число случайных входных данных', 'FontSize', 12);
% ylabel('Вероятность хотя бы одной коллизии, %', 'FontSize', 12);
% legend('experimentally','theoretical');
% 
% num_bit = 2^6;
% numFrames = 2;
% sum_err = 0;
% zz = 1;
% typeCrc = 2;
% maxFrames = 1002;
% 
% while numFrames <= maxFrames
%     
%     for kk = 1:num_exp
%         sum_err = sum_err + happay_fun_try(num_bit, numFrames, typeCrc);
%     end
%     
%     p_err(zz) = sum_err/num_exp;
%     step_vec(1, zz) = numFrames;
%     numFrames = numFrames + 100;
%     zz = zz + 1;
%     sum_err = 0;
% end
% 
% 
% n_max = 2^16;
% p1 = 1 - exp(-(step_vec.*(step_vec-1))/(2*n_max));
% 
% figure;
% plot(step_vec, p_err * 100, '-', 'LineWidth',2);
% grid on;
% hold on;
% plot(step_vec, p1 * 100,  '-', 'LineWidth', 2);
% 
% title('Расчет криптостойкости - CRC16', 'FontSize', 12);
% xlabel('Число случайных входных данных', 'FontSize', 12);
% ylabel('Вероятность хотя бы одной коллизии, %', 'FontSize', 12);
% legend('experimentally','theoretical');

num_bit = 2^9;
numFrames = 2;
sum_err = 0;
zz = 1;
typeCrc = 3;
maxFrames = 250002;
num_exp = 100;

while numFrames <= maxFrames
    
    for kk = 1:num_exp
        sum_err = sum_err + happay_fun_try(num_bit, numFrames, typeCrc);
    end
    
    p_err(zz) = sum_err/num_exp;
    step_vec(1, zz) = numFrames;
    numFrames = numFrames + 10000;
    zz = zz + 1;
    sum_err = 0;
end


n_max = 2^32;
p1 = 1 - exp(-(step_vec.*(step_vec-1))/(2*n_max));

figure;
plot(step_vec, p_err * 100, '-', 'LineWidth',2);
grid on;
hold on;
plot(step_vec, p1 * 100,  '-', 'LineWidth', 2);

title('Расчет криптостойкости - CRC32', 'FontSize', 12);
xlabel('Число случайных входных данных', 'FontSize', 12);
ylabel('Вероятность хотя бы одной коллизии, %', 'FontSize', 12);
legend('experimentally','theoretical');


















