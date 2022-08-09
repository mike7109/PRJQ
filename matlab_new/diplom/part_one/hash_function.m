%% Моделирование хеш-функций

clc; clear; close all;

hash_ref_one = get_hash(4, 4);
count_err = 0;

for i = 0:power(2,128)
    hash_ref = get_hash(i, 4);
    if ((hash_ref == hash_ref_one) & (i ~= 4))
        count_err = count_err + 1;
    end
end


% % numBite = 2048;
% % 
% % 
% % data_in = randi([0, 1], numBite, 8);
% % data_ref = '';
% % for ii = 1:size(data_in, 1)
% %     data_ref = strcat(data_ref,bin2hex(data_in(ii, 1:end)));
% % end
% % 
% % hash_ref = get_hash(data_ref, 4);
% % error_hash = 0;
% % 
% % for numTest = 1:100
% %     error = randi([0, 1], numBite, 8);
% %     data_err = bitxor(data_in, error);
% %     data_err_str = '';
% %     for ii = 1:size(data_err, 1)
% %         data_err_str = strcat(data_err_str,bin2hex(data_err(ii, 1:end)));
% %     end
% %     %get_hash - 
% %     data_out = get_hash(data_err_str, 4);
% %     if (hash_ref == data_out)
% %         error_hash = error_hash + 1;
% %     end
% % end
% 
% 
% %Сравнение входных и выходных данных
% % for ii=0:10
% %     data_err = data_in + 
% % end
% 
% gx = zeros(1, 32);
% gx( [27 24 23 17 13 12 11 9 8 6 5 3 2 1] ) = 1;
% 
% poly = 'z^32 + z^26 + z^23 + z^22 + z^16 + z^12 + z^11 + z^10 + z^8 + z^7 + z^5 + z^4 + z^2 + z + 1';
% 
% data = [0 0 0 0 1 0 1 0]';
% crcGen2 = comm.CRCGenerator(...
%     'Polynomial', poly, ...
%     'InitialConditions', 0, ...
%     'DirectMethod', 0, ...
%     'FinalXOR', 1);
% txSeq = crcGen2(data);
% csDirect = txSeq(end-31:end);
% 
% data_ref = bin2hex(csDirect');
