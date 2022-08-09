numFrames = 1000000;
poly = 'z16+z15+z2+1';
crcgenerator = comm.CRCGenerator(poly);
crcdetector = comm.CRCDetector(poly);

for enbo = 4:4
    for k = 1:numFrames
        data = randi([0 1],size_packet,1);                 % Generate binary data
        encData = crcgenerator(data);                   % Append CRC bits
        numerrs = 0;
        while 1
            demodData = bsc(encData,enbo/size_packet);
            [numerrs, ~] = biterr(demodData,encData);
            if numerrs == enbo
                break
            end
        end

        [dataTx,frmError] = crcdetector(demodData);     % Detect CRC errors
        sumErrorCrc = sumErrorCrc + frmError;
      
    end
p_err_2(enbo) = (numFrames-sumErrorCrc)/numFrames;
sumErrorCrc = 0;
end


