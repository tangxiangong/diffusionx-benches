clc
clear
close all

T = 100:100:1000;
x0 = 0;
D = 0.5;
tau = 0.01;
N = 10000;
m = zeros(length(T), 1);
tic
for k=1:length(T)
    m(k) = msd(T(k), x0, D, tau, N);
end
toc