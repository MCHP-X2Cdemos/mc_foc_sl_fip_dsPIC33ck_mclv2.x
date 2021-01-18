
//exec("./mtlbclr.sce");
xdel(winsid());
tic();
// Load simulation parameters
//exec("./parameters.sce");
//exec("./initProject.sce");

importXcosDiagram("MC_FOC_SL_FIP_dsPIC33CK_MCLV2.zcos");

xcos_simulate(scs_m, 4);
xdel(winsid());

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

//subplot(248);
//h4 = plot(qei_out.time, qei_out.values(:,1));
//title("dqei/dt");
//xgrid(1);

//scf(2);
//plot(dbg.time, dbg.values)
//title("dbg ch1 = blue, ch2 = green, ch3 = red");

//scf(1);
//plot(dbg1.time, dbg1.values)
//title("dbg1 ch1 = blue, ch2 = green, ch3 = red");

scf(2);
plot(dbg2.time, dbg2.values)
title("dbg2 ch1 = blue, ch2 = green, ch3 = red");
simulation_time = toc();
disp(simulation_time/60, "Simulation Time [min]")

