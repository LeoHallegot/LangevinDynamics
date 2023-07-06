#ifndef constants
#define constants

#include <vector>
#include <string>

// Choices of the potential and bias //
extern int bias_type, potential_type;
// ----- Constants ----- //
extern double m, gamma_Lang, kt, sigma;
// ----- Simulation parameters ----- //
extern double x_init, dt;
extern int num_steps, outfreq;  //prints 1 line every outfreq steps
/*extern int num_steps, outfreq;*/
// ----- Well parameters ----- //
extern double k, A, B, C;
// ----- Bias parameters ----- //
extern double k_bias, cstbias, v_bias;

class Inputs {
	public:
	Inputs() = default;
	~Inputs() = default;
	
	std::vector<double> vect_values;
	std::vector<std::string> vect_keywords;
	
	void default_initialization();
	void initialize_vectors();
	void read(std::string filename);
	void print_inputs();
	void init_values_with_input();
	
	void initialize_inputs(); // Should be done directly in read input?
	// TODO : implement this.
	
/*	// ----- Constants ----- //*/
/*	double m, kt, sigma, gamma_Lang;*/
/*	// ----- Simulation parameters ----- //*/
/*	double dt, x_init;*/
/*	int num_steps, outfreq;  //prints 1 line every outfreq steps*/
/*	// ----- Well parameters ----- //*/
/*	double k, A, B, C;*/
/*	// ----- Bias parameters ----- //*/
/*	double k_bias, cstbias, v_bias;*/
};



#endif

