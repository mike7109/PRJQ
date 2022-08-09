%%
clc; clear; close all;

n = 1;
p1 = 0.01;

n = 100;

Pn = zeros(1, n);

for ii = 1:n
    Pn(1, ii) = (1 - power((1 - p1), ii)) * 100;
end

n_step = 1:n;

figure;

plot(n_step, Pn);

grid on;
hold on;

title('График вероятности выхода из строя массива RAID 0');
xlabel('Количество носителей');
ylabel('Вероятность выхода, %');

%%
clc; clear; close all;

n = 7;

Pn = zeros(1, n);
n_step = zeros(1, n);
for ii = 1:n
    n_sum = power(2, ii) - 1;
    n_step(1, ii) = n_sum;
    Pn(1, ii) = ii/n_sum * 100;
end


figure;

plot(n_step, Pn);

grid on;
hold on;

title('Расчётное количество дисков для организации RAID 2');
xlabel('Всего дисков');
ylabel('Перерасход дисков, %');

%%
clc; clear; close all;

n = 40;

eff_1 = zeros(1, n);
eff_2 = zeros(1, n);
eff_4_5 = zeros(1, n);
eff_6 = zeros(1, n);

for ii = 1:n
    eff_1(1, ii) = 1/ii;
    eff_2(1, ii) = 1 - 1/ii * log2(ii+1);
    eff_4_5(1, ii) = 1 - 1/ii;
    eff_6(1, ii) = 1 - 2/ii;
    if (eff_6(1, ii) < 0)
         eff_6(1, ii) = 0;
    end
end

figure;

n_step = 1:n;

plot(n_step, eff_1 * 100, '-', 'LineWidth',2);

grid on;
hold on;

plot(n_step, eff_2 * 100, '-', 'LineWidth',2);
plot(n_step, eff_4_5 * 100, '-', 'LineWidth',2);
plot(n_step, eff_6 * 100, '-', 'LineWidth',2);

legend('RAID 1','RAID 2', 'RAID 4-5', 'RAID 6');

title('Расчётн эффективной ёмкости RAIDx', 'FontSize', 14);
xlabel('Всего дисков', 'FontSize', 14);
ylabel('Эффективная ёмкость, %', 'FontSize', 14);



