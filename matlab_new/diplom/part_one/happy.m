%%
clc; clear; close all;

z_ref = zeros(1, 50); % Random matrix

poly = [32,26,23,22,16,12,11,10,8,7,5,4,2,1,0];

crcGen2 = comm.CRCGenerator(...
    'Polynomial', poly, ...
    'InitialConditions', 1, ...
    'DirectMethod', true, ...
    'FinalXOR', 1);

ebno = 10;

cnt_err = 0;
n_size = 5*power(10, 5);
size_bit = 128;
z_ref = randi([0 1],n_size,64); % Random matrix
crc_ref = zeros(n_size, 64+32);
for ii = 1:n_size
    crc_ref(ii, 1:end) = crcGen2(z_ref(ii, 1:end)')';
end


for ii=1:1000
    new_paket = randi([0 1],64,1); % Random matrix
    txSeq_new = crcGen2(new_paket);
    for zz = 1:n_size
        if ~(isequal(crc_ref(zz, 1:end-32), txSeq_new(1:end-32)'))
            if (isequal(crc_ref(zz, end-31:end), txSeq_new(end-31:end)'))
                cnt_err = cnt_err + 1;
            end
        end
    end
end    




%[numerrs, pcterrs] = biterr(z,nz); % Number and percentage of errors




