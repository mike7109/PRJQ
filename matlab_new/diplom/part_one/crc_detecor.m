clc; clear; close all;

poly = 'z4+z3+z2+z+1';
poly = 'z8+z7+z6+z4+z2+1'; size_poly = 8;
%poly = 'z16+z15+z2+1'; size_poly = 16;
%poly = 'z32+z26+z23+z22+z16+z12+z11+z10+z8+z7+z5+z4+z2+z+1'; size_poly = 32;
% 

crcgenerator = comm.CRCGenerator(...
    'Polynomial', poly, ...
    'InitialConditions', 1, ...
    'DirectMethod', true, ...
    'FinalXOR', 1);

crcdetector = comm.CRCDetector(...
    'Polynomial', poly, ...
    'InitialConditions', 1, ...
    'DirectMethod', true, ...
    'FinalXOR', 1);

data = randi([0 1],16,1);                  % Generate binary data
encData = crcgenerator(data);                   % Append CRC bits

if (encData(3))
    encData(3) = 0;
else
    encData(3) = 1;
end

if (encData(6))
    encData(6) = 0;
else
    encData(6) = 1;
end

if (encData(7))
    encData(7) = 0;
else
    encData(7) = 1;
end

if (encData(11))
    encData(11) = 0;
else
    encData(11) = 1;
end

demodData = encData;
[dataTx,frmError] = crcdetector(demodData);

if (~isequal(data,dataTx))
   sumData = sumData + 1;
end


% numFrames = 1*10^6;
% 
% num_bit = 2^6;
% max_bit = 2^16;
% step_bit = 2;
% 
% size_vec = log2(max_bit) - log2(num_bit) + 1;
% 
% dataTx = zeros(num_bit,1);
% frmError = 0;
% sumData = 0;
% sumData_vec = zeros(size_vec,1);
% sumErrorCrc = 0;
% sumErrorCrc_vec = zeros(size_vec,1);
% per_errCrc = zeros(size_vec,1);
% demodData = zeros(num_bit+size_poly,1);
% zz = 1;
% 
% tic
% while num_bit <= max_bit
%     demodData = zeros(num_bit+size_poly,1);
%     for k = 1:numFrames
%         data = randi([0 1],num_bit,1);                  % Generate binary data
%         encData = crcgenerator(data);                   % Append CRC bits
%         demodData = [bsc(data,.01); encData(end-size_poly-1:end)];
%         [dataTx,frmError] = crcdetector(demodData);     % Detect CRC errors
%         sumErrorCrc = sumErrorCrc + frmError;
%         if (~isequal(data,dataTx))
%            sumData = sumData + 1;
%         end
%     end
%     per_errCrc(zz) = (sumData - sumErrorCrc) / sumData;
%     zz = zz + 1;
%     num_bit = num_bit * step_bit;
% end
% toc







% S_err = sum(numerrs)/numFrames;
% S_perr = sum(pcterrs)/numFrames;

