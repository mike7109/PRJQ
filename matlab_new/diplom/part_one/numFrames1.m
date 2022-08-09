clc; clear; close all;

poly = 'z4+z3+z2+z+1';
crcgenerator = comm.CRCGenerator(poly);
crcdetector = comm.CRCDetector(poly);

numFrames = 20;
frmError = zeros(numFrames,1);

for k = 1:numFrames
    data = randi([0 1],12,1);                 % Generate binary data
    encData = crcgenerator(data);                   % Append CRC bits
    modData = pskmod(encData,2);              % BPSK modulate
    rxSig = awgn(modData,5);                  % AWGN channel, SNR = 5 dB
    demodData = pskdemod(rxSig,2);            % BPSK demodulate
    [~,frmError(k)] = crcdetector(demodData); % Detect CRC errors
end