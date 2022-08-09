function [outputArg1] = happay_fun_try(num_bit,numFrames,typeCrc)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here

switch typeCrc
    case 1
        poly = 'z8+z7+z6+z4+z2+1'; 
        size_poly = 8;
    case 2
        poly = 'z16+z15+z2+1'; 
        size_poly = 16;
    case 3
        poly = 'z32+z26+z23+z22+z16+z12+z11+z10+z8+z7+z5+z4+z2+z+1'; 
        size_poly = 32;
end

crcgenerator = comm.CRCGenerator(...
    'Polynomial', poly, ...
    'InitialConditions', 1, ...
    'DirectMethod', true, ...
    'FinalXOR', 1);

encData = zeros(numFrames,num_bit+size_poly);

z = 1;

for k = 1:numFrames
    data = randi([0 1],num_bit,1);                  % Generate binary data
    encData(k, 1:end) = crcgenerator(data)';                   % Append CRC bits
    while z < k
        if isequal(encData(k, 1:end),encData(z, 1:end))
            encData(k, 1:end) = crcgenerator(data);
            z = 1;
        end
        z = z + 1;
    end
end

seccses = 0;

[C,~,~] = unique(encData(:,end-size_poly+1:end),'rows');

if size(C, 1) ~= size(encData, 1)
    seccses = 1;
end


% for ii = 1:numFrames-1
%     for jj = ii+1:numFrames
%         if (isequal(encData(ii, end-size_poly+1:end),encData(jj, end-size_poly+1:end)))
%             seccses = 1;
%             break
%         end
%     end
%     if seccses
%         break
%     end
% end

outputArg1 = seccses;
end

