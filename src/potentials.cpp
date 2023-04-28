#include <cmath>
#include <functional>
#include <iostream>
#include "potentials.h"
#include "constants.h"

extern const double k, A, B;
extern const double k_bias, cstbias, alpha;


// ~~~~~~~~~ Constants biases ~~~~~~~~~ //

// -- No bias -- //
double Vbias_nul(double /* x */, double /* t */) {
	return 0.;
}
double gradVbias_nul(double /* x */, double /* t */) {
	return 0.;
}

// -- Constant bias -- //
double Vbias_const(double x, double /* t */) {  //But only outside of the barrier.
	if (A*pow(x,4) - B*pow(x,2) < cstbias){return  cstbias;}
	else {return 0.;}
}
double gradVbias_const(double /* x */) {
	return 0.; 
}

// -- Harmonic bias -- //
double Vbias_harm(double x, double /* t */) {
	return  0.5*k_bias*x*x;
}
double gradVbias_harm(double x, double /* t */) {
	return k_bias*x;
}


// ~~~~~~~~~ Time dependants biases ~~~~~~~~~ //

// -- Adiabatic bias MD -- //
double Vbias_ABMD(double x, double /* t */) {
	static double G0 = x;
	if (x > G0) {
		G0 = x;
		return 0.;
	} else {
		return 0.5*k_bias*(x-G0)*(x-G0);
	}
} // incrémentation de G0=x only.

double gradVbias_ABMD(double x, double /* t */) {
	static double G0 = x;
	if (x > G0) {
		G0 = x;
		return 0.;
	} else {
		return k_bias*(x-G0);
	}
}

// -- Steered MD -- //
// The potential energy profile increase rapidly with timestep forcing the particule to go to high energy levels.
// Problem/bug supposed.

// Weird behavior obtained with v=0.0005; k=0.005 => the system was able to switch back to left well
// TODO : implement steered correctly
double Vbias_steered(double x, double t) {
	static double t_local = 0.;
	double x_init = -4.0;
	double x_ref = x_init + v_bias*t_local;
	t_local += dt;
	return 0.5*k_bias*(x - x_ref)*(x - x_ref);
}

double gradVbias_steered(double x, double t) {
	static double t_local = 0.;
	double x_init = -4.0;
	double x_ref = x_init + v_bias*t_local;
	t_local += dt;
	return k_bias*(x - x_ref);
}


// ~~~~~~~~~ Total potentials ~~~~~~~~~ //

////Harmonic potential function
//double V_harm(double x) {
//    return 0.5 * k * x * x;
//}
//double gradV_harm(double x) {
//    return k * x;
//}

//// Double well potential
//double V_dblwl(double x) {  //Double puit harmonique
//	return  A*pow(x,4) - B*pow(x,2) + C + Vbias(x);
//}
//double gradV_dblwl(double x) {
//	return 4.0*A*pow(x,3) - 2.0*B*x + gradVbias(x);
//}

