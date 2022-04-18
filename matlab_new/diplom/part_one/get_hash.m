function [data_out] = get_hash(data_in, typeHesh)
%get_hesh Summary of this function goes here
%   Detailed explanation goes here
str = data_in;

switch typeHesh
    case 1
        hasher = System.Security.Cryptography.SHA256Managed;
    case 2
        hasher = System.Security.Cryptography.SHA384Managed;
    case 3
        hasher = System.Security.Cryptography.SHA512Managed;
    case 4
        hasher = System.Security.Cryptography.SHA1Managed;
end


%Преобразуем в одну строчку
rslt_hash = uint8(hasher.ComputeHash(uint8(str)));
rslt_hash = dec2hex(rslt_hash)';
rslt_hash = reshape(rslt_hash,1,[]);


data_out = rslt_hash;
end

