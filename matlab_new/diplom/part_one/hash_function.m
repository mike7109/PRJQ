%% Моделирование хеш-функций

clc; clear; close all;
numBite = 2048;


data_in = randi([0, 1], numBite, 8);
data_ref = '';
for ii = 1:size(data_in, 1)
    data_ref = strcat(data_ref,bin2hex(data_in(ii, 1:end)));
end

hash_ref = get_hash(data_ref, 4);
error_hash = 0;

for numTest = 1:100
    error = randi([0, 1], numBite, 8);
    data_err = bitxor(data_in, error);
    data_err_str = '';
    for ii = 1:size(data_err, 1)
        data_err_str = strcat(data_err_str,bin2hex(data_err(ii, 1:end)));
    end
    %get_hash - 
    data_out = get_hash(data_err_str, 4);
    if (hash_ref == data_out)
        error_hash = error_hash + 1;
    end
end


%Сравнение входных и выходных данных
% for ii=0:10
%     data_err = data_in + 
% end
