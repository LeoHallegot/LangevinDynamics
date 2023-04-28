#ifndef potentials
#define potentials


// ~~~~~~~~~ Constants biases ~~~~~~~~~ //


// No bias
double Vbias_nul(double /* x */);
double gradVbias_nul(double /* x */);

// constant bias
double Vbias_const(double x);
double gradVbias_const(double /* x */);

//Harmonic bias
double Vbias_harm(double x);
double gradVbias_harm(double x);


// ~~~~~~~~~ Time dependants biases ~~~~~~~~~ //
// Adiabatic bias
double Vbias_ABMD(double x);
double gradVbias_ABMD(double x);

// Steered bias
double Vbias_steered(double x);
double gradVbias_steered(double x);


/*
//Harmonic potential function
double V_harm(double x);
double gradV_harm(double x);

// Double well potential
double V_dblwl(double x);
double gradV_dblwl(double x);
*/

#endif
