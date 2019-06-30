// Simulation settings
endTime     = 5;
stepSize    = 1.0E-2;
X2C_sampleTime = 0.0001;

// MOTORDATEN
Nm_ozin = 7.061552e-3;
KRPM_rads = 0.060/2/%pi;

Rs = 4.03;
Ld = 4.60e-3;
Lq = 4.60e-3;
Kell = 7.24;
n_p = 5;        // number of polepairs

Vbus = 24;
Rshunt = 0.025;
Igain = -15;

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



// Umrechnen auf Rechnenwerte fuer Modell
Ld = Ld/2;
Lq = Lq/2;
Rs = Rs/2;

psi_pm = Kell/sqrt(3)*60/(2*%pi*1000)/n_p;

theta_r0 = theta_m0*2*%pi*n_p;
omega_r0 = omega_m0/60*2*%pi*n_p;


// initalize input for simulation
exec("./gen_inputs.sci");
exec("./qei_sim.sce");
exec("./qei_sim2.sce");






