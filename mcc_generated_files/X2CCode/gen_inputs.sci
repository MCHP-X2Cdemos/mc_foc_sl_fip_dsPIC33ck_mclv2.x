simulation_time = 5;
//// timeing for omega
//tw1 = 0.7;
//tw2 = 0.3;
//tw3 = 2.5;
//tw4 = 0.3;
//tw5 = 0.1;
//tw6 = 0.05;
//
//// omega steps
//w1 = 0.2;
//w2 = 0.4;
//w3 = 0.6;
//
//// timinig for load
//tl1 = 0.3;
//tl2 = 0.7;
//tl3 = 2.0;
//tl4 = 0.3;
//tl5 = 1.0;
//tl6 = 0.3;
//
//// load steps
//l1 = 0.0;
//l2 = 0.01;
//l3 = 0.01;

// timeing for omega
tw1 = 0.3;
tw2 = 0.3;
tw3 = 2.5;
tw4 = 0.3;
tw5 = 1.5;
tw6 = 0.1;

// omega steps
w1 = 0.0;
w2 = 0.1;
w3 = 0.1;

// timinig for load
tl1 = 0.3;
tl2 = 0.3;
tl3 = 2.8;
tl4 = 0.3;
tl5 = 1;
tl6 = 0.3;

// load steps
l1 = 0.0;
l2 = 0.01;
l3 = 0.01;

if (tw1+tw2+tw3+tw4+tw5+tw6)> simulation_time then
   mprintf('calculated time for omega is longer than simulation_time '); 
end

if (tl1+tl2+tl3+tl4+tl5+tl6)> simulation_time then
   mprintf('calculated time for load is longer than simulation_time '); 
end

t = (0:0.01:simulation_time);

omega_input.time = t';
omega_input.values(find(0 <= t & t < tw1)) = w1;
omega_input.values(find(tw1 <= t & t < tw1+tw2)) = linspace(w1,w2,size(find(tw1 <= t & t < tw1+tw2),"c"))';
omega_input.values(find(tw1+tw2 <= t & t < tw1+tw2+tw3)) = w2;
omega_input.values(find(tw1+tw2+tw3 <= t & t < tw1+tw2+tw3+tw4)) = linspace(w2,w3,size(find(tw1+tw2+tw3 <= t & t < tw1+tw2+tw3+tw4),"c"))';
omega_input.values(find(tw1+tw2+tw3+tw4 <= t & t < tw1+tw2+tw3+tw4+tw5)) = w3;
omega_input.values(find(tw1+tw2+tw3+tw4+tw5 <= t & t < tw1+tw2+tw3+tw4+tw5+tw6)) = linspace(w3,0.0,size(find(tw1+tw2+tw3+tw4+tw5 <= t & t < tw1+tw2+tw3+tw4+tw5+tw6),"c"))';
omega_input.values(find(tw1+tw2+tw3+tw4+tw5+tw6 <= t & t <= simulation_time)) = 0;


t_load.time = t';
t_load.values(find(0 <= t & t < tl1)) = l1;
t_load.values(find(tl1 <= t & t < tl1+tl2)) = linspace(l1,l2,size(find(tl1 <= t & t < tl1+tl2),"c"))';
t_load.values(find(tl1+tl2 <= t & t < tl1+tl2+tl3)) = l2;
t_load.values(find(tl1+tl2+tl3 <= t & t < tl1+tl2+tl3+tl4)) = linspace(l2,l3,size(find(tl1+tl2+tl3 <= t & t < tl1+tl2+tl3+tl4),"c"))';
t_load.values(find(tl1+tl2+tl3+tl4 <= t & t < tl1+tl2+tl3+tl4+tl5)) = l3;
t_load.values(find(tl1+tl2+tl3+tl4+tl5 <= t & t < tl1+tl2+tl3+tl4+tl5+tl6)) = linspace(l3,0,size(find(tl1+tl2+tl3+tl4+tl5 <= t & t < tl1+tl2+tl3+tl4+tl5+tl6),"c"))';
t_load.values(find(tl1+tl2+tl3+tl4+tl5+tl6 <= t & t <= simulation_time)) = 0;

scf(2);
subplot(211);
h1 = plot(t_load.time, t_load.values);
title("Tload");
xgrid(1);

subplot(212);
h1 = plot(omega_input.time, omega_input.values);
title("Omega");
xgrid(1);
