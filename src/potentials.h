#ifndef potentials
#define potentials


// ~~~~~~~~~ Constants biases ~~~~~~~~~ //


// No bias
double Vbias_nul(double /* x */, double /* t */);
double gradVbias_nul(double /* x */, double /* t */);

// constant bias
double Vbias_const(double x, double /* t */);
double gradVbias_const(double /* x */, double /* t */);

//Harmonic bias
double Vbias_harm(double x, double /* t */);
double gradVbias_harm(double x, double /* t */);


// ~~~~~~~~~ Time dependants biases ~~~~~~~~~ //
// Adiabatic bias
double Vbias_ABMD(double x, double /* t */);
double gradVbias_ABMD(double x, double /* t */);

// Steered bias
double Vbias_steered(double x, double t);
double gradVbias_steered(double x, double t);
//Back and forth
double Vbias_ABMD_AR(double x, double /* t */);
double gradVbias_ABMD_AR(double x, double /* t */);

double Vbias_steered_AR(double x, double t);
double gradVbias_steered_AR(double x, double t);


/*
//Harmonic potential function
double V_harm(double x);
double gradV_harm(double x);

// Double well potential
double V_dblwl(double x);
double gradV_dblwl(double x);
*/

#endif
