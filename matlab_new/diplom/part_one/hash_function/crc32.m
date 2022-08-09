function [result, hex] = crc32(data)

gx = zeros(1, 32);
gx( [27 24 23 17 13 12 11 9 8 6 5 3 2 1] ) = 1;

data_len = length(data);
 
result = dec2bin(0 , 32 ) - '0';
for k=1:data_len
    temp = dec2bin( data(k),32 ) - '0';
    for m = 1:32
        if result(32) ~= temp(m)
            result(1:32) = [ 0 result(1:31) ];
            result = xor(result,gx);
        else
            result(1:32) = [0 result(1:31)];
        end
    end
end
 
str = num2str(fliplr(result));
hex = dec2hex( bin2dec(str),8 );

end

