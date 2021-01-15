// Plots
scf(10);
subplot(241);
h4 = plot(omega_input.time, omega_input.values);
title("OmegaSet");
xgrid(1);

subplot(242);
h1 = plot(motor_in.time, motor_in.values(:,5));
title("Tload");
xgrid(1);

subplot(243);
h1 = plot(motor_in.time, motor_in.values(:,1:3));  
title("Vabc");
xgrid(1);

subplot(244);
h1 = plot(motor_in.time, motor_in.values(:,4));
title("Vq");
xgrid(1);

subplot(245);
h3 = plot(motor_out.time, motor_out.values(:,4));
title("omega");
xgrid(1);

subplot(246);
h4 = plot(motor_out.time, motor_out.values(:,5));
title("torque");
xgrid(1);

subplot(247);
h2 = plot(motor_out.time, motor_out.values(:,1:3));
title("Iabc");
xgrid(1);

subplot(248);
h4 = plot(motor_out.time, motor_out.values(:,6));
title("angle_qei");
xgrid(1);

scf(20);
plot(dbg2.time, dbg2.values)
title("dbg2 ch1 = blue, ch2 = green, ch3 = red");

mprintf('simulation time = %d3.2 min',simulation_time);
