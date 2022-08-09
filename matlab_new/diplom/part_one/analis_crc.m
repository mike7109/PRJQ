%%
clc; clear; close all;

z_ref = randi([0 1],4096,1); % Random matrix

poly = [32,26,23,22,16,12,11,10,8,7,5,4,2,1,0];

crcGen2 = comm.CRCGenerator(...
    'Polynomial', poly, ...
    'InitialConditions', 1, ...
    'DirectMethod', true, ...
    'FinalXOR', 1);


cnt_err = 0;

for ii=1:10000
    z_ref = randi([0 1],128,1); % Random matrix
    txSeq = crcGen2(z_ref);
    csDirect = txSeq(end-31:end);
    nz = bsc(z_ref,0.05); % Binary symmetric channel
    txSeq_new = crcGen2(nz);
    csDirect_new = txSeq_new(end-31:end);
    if ~(isequal(nz, z_ref))
        if (isequal(csDirect, csDirect_new))
            cnt_err = cnt_err + 1;
        end
    end
end    


%[numerrs, pcterrs] = biterr(z,nz); % Number and percentage of errors




