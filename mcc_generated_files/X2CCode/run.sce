// simulate project with loaded
// ModelParamters.sce
// save simulation results in a file
// show simulation result
xdel(winsid());
tic();                          // start time measurement
importXcosDiagram("MC_FOC_SL_FIP_dsPIC33CK_MCLV2.zcos");
xcos_simulate(scs_m, 4);
xdel(winsid());
simulation_time = toc()/60;     // store simulation time in min

exec('save_simulation.sce');    // safe simulation results
exec('show_simulation.sce');    // show simulation results
