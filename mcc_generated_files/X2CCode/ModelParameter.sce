// Simulation settings
endTime     = 5;
stepSize    = 1.0E-2;
X2C_sampleTime = 0.0001;

// CODE GENERATION PARAMETERS

// Speed PI
SpeedKi = 1;
SpeedKi = 0.5;

// Current PI
PIFluxKp = 0.8;
PIFluxKi = 0.5;

PITorqueKp = 0.8;
PITorqueKi = 0.5;

// PLL parameters
MotorLs = 0.41;
MotorRs = 0.35;
U_DCLINK = 24;
I_MAX = 3.95;
BEMF_D_UDC = 0.65;
PLL_INT = 800;









// POWERSTAGE DATA
Vbus = 24;
Rshunt = 0.025;
Igain = -15;

// MOTORDATEN
Nm_ozin = 7.061552e-3;
KRPM_rads = 0.060/2/%pi;

Rs = 4.03;
Ld = 4.60e-3;
Lq = 4.60e-3;
Kell = 7.24;
n_p = 5;        // number of polepairs


J = 0.000628 * Nm_ozin;   // inertia
cf = 0;
chy = 0;
d = 0;
ced = 0;
ded = 0;

alphaCU = 0;
alphaPM = 0;
Temp_nom = 25;
omega_m0 = 0;
theta_m0 = -0.5;
psi_pm = Kell/sqrt(3)*60/(2*%pi*1000)/n_p;
theta_r0 = theta_m0*2*%pi*n_p;
omega_r0 = omega_m0/60*2*%pi*n_p;










// Umrechnen auf Rechnenwerte fuer Modell
Ld = Ld/2;
Lq = Lq/2;
Rs = Rs/2;




// initalize input for simulation
exec("./gen_inputs.sci");
exec("./qei_sim.sce");
exec("./qei_sim2.sce");






