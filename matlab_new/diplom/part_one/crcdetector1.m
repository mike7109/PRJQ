function [outputArg1,outputArg2] = crcdetector(inputArg1)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

%poly = 'z4+z3+z2+z+1';
poly = 'z8+z7+z6+z4+z2+1';
% poly = 'z16+z15+z2+1'; size_poly = 16;
%poly = 'z32+z26+z23+z22+z16+z12+z11+z10+z8+z7+z5+z4+z2+z+1'; size_poly = 32;

crcdetector = comm.CRCDetector(poly);

[outputArg1,outputArg2] = crcdetector(inputArg1);

end

