#include "constants.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// Choices of the potential and bias //
int bias_type, potential_type;
// ----- Constants ----- //
double m, gamma_Lang, kt, sigma;
// ----- Simulation parameters ----- //
double x_init, dt;
int num_steps, outfreq;  //prints 1 line every outfreq steps
/*extern int num_steps, outfreq;*/
// ----- Well parameters ----- //
double k, A, B, C;
// ----- Bias parameters ----- //
double k_bias, cstbias, v_bias;


// TODO : tester si il est possible d'initialiser ces variables comme globales sans avoir à les appeler I.variable
// TODO : ajouter la possibilité de ne pas lire les commentaires dans le fichier d'input. Vérifier si 
//        il est possible de sauter des lignes ou non.
// TODO : put reading and initialization of the values in the same function ?
// TODO : in read(), if some keyword is not found, give default value ?
// TODO : find a way to be able to read the names of the biases and potentials in the input instead of a number ?

void Inputs::default_initialization() {
//Inputs::Inputs() { //Default initialization if there is no input file.
    // Choices of the potential and bias //
    bias_type = 3;
    potential_type = 1;
	m = 1.0; // Mass of particle
	gamma_Lang = 10.0; // Friction coefficient
	kt = 1.0;
	// ----- Simulation parameters ----- //
	x_init = -4.35; //Starting position
	dt = 0.001; // Time step
	num_steps = 35000000; //Number of simulation steps
	outfreq = 1000;  //prints 1 line every outfreq steps
	// ----- Well parameters ----- //
	k = 1.0;  // Spring constant (single harmonic well)
	A = 0.05; // A, B and C : constant for double well
	B = 1.2;  // Ax⁴+Bx²+C
	// C : normalisation, make min(V(x))=0 and barrier heigth = C.
	// A = 0.05, B=1.2 -> C = 7.2  // A=0.05, B=0.8 -> C = 3.2 kbT
	// ----- Bias parameters ----- //
	// - constant - //
	k_bias = 0.55; //harmonic restraint
	cstbias = C/2.0; //constant bias
	// - computed - //
	sigma = sqrt((1.0 - exp(-2.0 * gamma_Lang * dt)) * m * kt);
	C = abs( A*pow(sqrt(B/(2*A)),4) - B*pow(sqrt(B/(2*A)),2) );
	// - time-dependant - //
	v_bias = 10.0/(dt*num_steps); // x~[-5;5]; time to walk the entire path ~ 10/v_bias
									  // we want at *least* 10.000 time steps => v_bias<0.001.
}

void Inputs::initialize_vectors() {
	vect_keywords.push_back("inital_pos");
	vect_keywords.push_back("mass");
	vect_keywords.push_back("gamma");
	vect_keywords.push_back("BoltzmannTemp");
	vect_keywords.push_back("timestep");
	vect_keywords.push_back("numb_of_steps");
	vect_keywords.push_back("output_freq");
	vect_keywords.push_back("spring_const_unbiased");
	vect_keywords.push_back("double_well_A");
	vect_keywords.push_back("double_well_B");
	vect_keywords.push_back("spring_const_biased");
	vect_keywords.push_back("Type_of_the_potential");
	vect_keywords.push_back("Type_of_the_bias");
	vect_values.resize(vect_keywords.size());
}


void Inputs::read(string filename) {
	ifstream infile;
	string line;
	string keyword;
	double value;
	int i;
	infile.open(filename);
	int nline=0;
	while( infile.peek() != EOF ) { //EOF = end of file
		infile >> keyword >> value;
//		cout<<keyword<<" "<<value<<endl; // DEBUG
		i=0;
		while( keyword != vect_keywords[i] ) {
//		    cout<<keyword<<" "<<vect_keywords[i]<<endl; // DEBUG
			i+=1;
			if ( i > vect_keywords.size() ) {
				cout<<"error, "<<keyword<<" not found"<<endl;
				break;
			}
		}
		vect_values[i] = value;
		nline = nline+1;
	}
}

void Inputs::print_inputs() {
    // TODO : doesnt print the right values in the default case since the vectors stay uninitialized.
    cout<<"##### ~~~~ Input values ~~~~ ##### "<<endl;
	for( int i=0; i<vect_values.size(); i++ ){
		cout<<i<<" "<<vect_keywords[i]<<" "<<vect_values[i]<<endl;
	}
	cout<<"##### ~~~~ --- ~~~~ ##### "<<endl;
}

void Inputs::init_values_with_input() {
	x_init = vect_values[0];
	m = vect_values[1]; // Mass of particle
	gamma_Lang = vect_values[2]; // Friction coefficient
	kt = vect_values[3];
	// ----- Simulation parameters ----- //
	dt = vect_values[4]; // Time step
	num_steps = vect_values[5]; //Number of simulation steps
	outfreq = vect_values[6];  //prints 1 line every outfreq steps
	// ----- Well parameters ----- //
	k = vect_values[7];  // Spring constant (single harmonic well)
	A = vect_values[8]; // A, B and C : constant for double well
	B = vect_values[9];  // Ax⁴+Bx²+C
	// ----- Bias parameters ----- //
	// - constant - //
	k_bias = vect_values[10]; //harmonic restraint
	// Choices of the potential and bias //
	bias_type = vect_values[12];
    potential_type = vect_values[11];
	// - computed - //
	sigma = sqrt((1.0 - exp(-2.0 * gamma_Lang * dt)) * m * kt);
	C = abs( A*pow(sqrt(B/(2*A)),4) - B*pow(sqrt(B/(2*A)),2) );
	cstbias = C/2.0; //constant bias
	// - time-dependant - //
	v_bias = 10.0/(dt*num_steps); // x~[-5;5]
}

