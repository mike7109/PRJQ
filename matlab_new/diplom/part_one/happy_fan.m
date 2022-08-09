clc; clear; close all;

n_max = power(2, 32);

number = 2^18;

n = 1:number;

p1 = 1 - exp(-(n.*(n-1))/(2*n_max));

plot(n, p1)

num_exp = power(2, 256);
p = 1 - exp(-(num_exp*(num_exp-1))/(2*n_max));