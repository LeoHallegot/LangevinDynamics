#ifndef constants
#define constants

/*void initialize_const();*/

// ----- Constants ----- //
extern const double m, gamma_Lang, dt, kt, sigma;
/*extern const double m, dt, kt, sigma;*/
/*extern double gamma_Lang*/
// ----- Simulation parameters ----- //
extern const int num_steps, outfreq;  //prints 1 line every outfreq steps
/*extern int num_steps, outfreq;*/
// ----- Well parameters ----- //
extern const double k, A, B, C;
// ----- Bias parameters ----- //
extern const double k_bias, cstbias, v_bias;

/*	extern int num_steps = values[0];*/
/*	extern int outfreq = values[1];*/
/*	extern double gamma_Lang = values[2];*/
#endif
