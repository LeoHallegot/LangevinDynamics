#include "constants.h"
#include "potentials.h"
#include "langevin_dynamics.h"

extern int bias_type;
extern all_bias_availables;

void chosebias(int bias) {
		switch (bias_type) {
		case unbiased :
			Vbias = Vbias_nul;
			gradVbias = gradVbias_nul;
			cout<<"Unbiased simulation"<<endl;
			break;
		case constant :
			Vbias = Vbias_const;
			gradVbias = gradVbias_const;
			cout<<"Constant bias applied (constant outside the barrier)"<<endl;
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
}
