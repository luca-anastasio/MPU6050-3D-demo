clc
clear all
close all

% dimostrazione della funzione fir1

fc = 10000;

f0 = 50;
f1 = 1500;
ft = 100;

N = 1000;
Nf = 20;

t = [0:N];

h = fir1(Nf, ft/fc);
hf = freqz(h, 1, 100);

x = cos(2*pi*(f0/fc)*t) + 0.1*cos(2*pi*(f1/fc)*t);

y = conv(x, h);

subplot(2, 2, 1);
stem(h);
xlabel('risposta impulsiva del filtro');

subplot(2, 2, 2);
plot(real(hf));
xlabel('risposta in frequenza del filtro');

subplot(2, 2, 3);
plot(x);
xlabel('segnale in ingresso');

subplot(2, 2, 4);
plot(y);
xlabel('segnale filtrato');