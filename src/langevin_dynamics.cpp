#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <functional>
#include "constants.h"
#include "potentials.h"

//#include <typeinfo>

using namespace std;


// Random number generator
random_device rd;
mt19937 gen(rd());
normal_distribution<double> dist(0.0, 1.0);

enum bias_type_t {
	nobias,
	constant,
	harmonic,
	ABMD,
	steered,
	n_bias_types
	};
enum {
	harmonic_potential,
	dblwl,
	};

// Passer la fonction en argument si pas d'autres solutions.
// ----- Potential functions ----- //
std::function<double(double, double)> V, gradV, Vbias, gradVbias;
//Harmonic potential function
double V_harm(double x, double /* t */) {
    return 0.5 * k * x * x;
}
double gradV_harm(double x, double /* t */) {
    return k * x;
}
// Double well potential
double V_dblwl(double x, double t) {  //Double puit harmonique
	return  A*pow(x,4) - B*pow(x,2) + C + Vbias(x,t);
}
double gradV_dblwl(double x, double t) {
	return 4.0*A*pow(x,3) - 2.0*B*x + gradVbias(x,t);
}


// #### ------- Main code ------- #### //

// BAOA (GSD) integrator as formulated in https://doorg/10.1021/acs.jctc.2c00585
// Code taken from colvar module : https://github.com/Colvars/colvars
double BAOA(double &x, double &v, double &t) {
	double Ekin;
	// starting from x_t, f_t, v_(t-1/2)
	// [B] Eq. (10a) split into two half-steps
	// This reduces to leapfrog when gamma = 0
	v  -= 0.5 * dt * gradV(x, t) / m;
// Kinetic energy at t
	Ekin = 0.5 * m * v * v;
	v  -= 0.5 * dt * gradV(x, t) / m;
	// Final v lags behind x by half a timestep
	// [A] Half step in position (10b)
	x += dt * v / 2.0;
	// [O] leap to v_(i+1/2) (10c)
	v *= exp(- 1.0 * dt * gamma_Lang);
	double eta = dist(gen);
	// ext_sigma has been computed at init time according to (10c)
	v += sigma * eta / m;
	// [A] Second half step in position (10d)
	x  += dt * v / 2.0;
	return Ekin;  //might not need Ekin all the time and change BAOA() to void BAOA()
}

// Main simulation function
void simulate() {
    double x = x_init; // Initial position
    double v = 0.5;  //Initial velocity
//	double v = dist(gen); //Random init vel
    double t = 0.0; // Initial time
    double Ekin;
    
    ofstream input_optle;
	input_optle.open("colvar");
	ofstream total_file;
	total_file.open("traj.dat");
	ofstream energy_file;
	energy_file.open("energies.dat");
	
    for (int i = 0; i < num_steps; i++) {
        Ekin = BAOA(x, v, t); // Update position, velocity, and time using BAOA integrator
        double x_bias = x_init + v_bias*t; //For SMD
        if (i%outfreq == 0) {
		    input_optle << t << "\t" << x << endl;  //Writing colvar file for unbiased optle.
		    total_file << t << "\t" << x << "\t" << -gradVbias(x,t) << "\t" << v << endl; // More complete ouput for biased optle.
        	energy_file << t << "\t" << Ekin << "\t" << V(x,t) << "\t" << Ekin+V(x,t) << "\t" << Vbias(x,t) <<endl;
        	//energy : set gamma to 0, allows to check if newtonian dynamics is ok.
        }
		t+=dt;
		
		if (bias_type>0) {
			if (abs(V(x, t)) > 2.1*abs(C)) { //add a x>0 condition ?
				cout<<"Stoping the simulation at t="<<t<<", x="<<x<<", V(x,t)="<<V(x,t)<<endl;
				cout<<"The particule reached a potential that is more than twice the theoretical barrier H="<<C<<endl;
				break; //Arbitrary : if the particule goes too high on the sides we stop.
				// Useful only with biased potentials.
			}
		}
    }
    input_optle.close();
    total_file.close();
    energy_file.close();
}

// Main function
int main(int argc, char* argv[]) {
    Inputs I;
    I.initialize_vectors();
    if (argc == 1) { //If inputfile read it, otherwise default
        I.default_initialization();
        cout<<"No input given, defaut values are used"<<endl;
    } else if (argc == 2) {
	    string input_file = argv[1];
	    cout<<"reading from "<<input_file<<endl;
	    I.read(input_file);
	    I.init_values_with_input();
    } else {
        cout<<"Too many arguments"<<endl;
        exit(EXIT_FAILURE);
    }
    I.print_inputs();
    
    cout<<bias_type<<" "<<ABMD<<" "<<potential_type<<endl;
    
	switch (bias_type) {
		case nobias :
			Vbias = Vbias_nul;
			gradVbias = gradVbias_nul;
			cout<<"Unbiased simulation"<<endl;
			break;
		case harmonic :
			Vbias = Vbias_harm;
			gradVbias = gradVbias_harm;
			cout<<"Harmonic bias applied"<<endl;
			break;
		case ABMD :
			Vbias = Vbias_ABMD;
			gradVbias = gradVbias_ABMD;
			cout<<"ABMD bias applied"<<endl;
			break;
		case steered :
			Vbias = Vbias_steered;
			gradVbias = gradVbias_steered;
			cout<<"Steered bias applied"<<endl;
			break;
		default :
			cout<<"No bias chosen, default unbiased"<<endl;
			Vbias = Vbias_nul;
			gradVbias = gradVbias_nul;
			break;
	}

	cout<<"Double well potential, barrier "<<C<<" kbT"<<endl<<endl;
	switch (potential_type) {
		case harmonic_potential :
			V = V_harm;
			gradV = gradV_harm;
			cout<<"harmonic potential"<<endl;
			break;
		case dblwl :
			V = V_dblwl;
			gradV = gradV_dblwl;
			cout<<"double well potential"<<endl;
			break;
		default :
			cout<<"no potential chosen"<<endl;
			V = V_dblwl;
			gradV = gradV_dblwl;
			cout<<"By default, using double well potential"<<endl;
			break;
	}
	simulate();
//	cout<<"Analytic form of the well : "<<A<<"*x**4 - "<<B<<"*x**2 + "<<C<<endl;
	if (bias_type == harmonic) {
		cout<<"Biased potential : "<<0.5*k_bias<<" * x**2"<<endl;
		cout<<"total : "<<A<<"*x**4 - "<<B<<"*x**2 + "<<C<<" + "<<0.5*k_bias<<" * x**2"<<endl;
	}
	cout<<endl<<"simulation completed normally"<<endl;
    return 0;
}

