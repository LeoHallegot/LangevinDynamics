#ifndef potentials
#define potentials


/*class position {*/
/*	*/
/*}*/

/*class Params {*/

/*	*/
/*}*/

/*double bias_potential::V(double x, double t) {*/
/*	switch (bias_type) {*/
/*		case nobias :*/
/*			Vbias = Vbias_nul;*/
/*			gradVbias = gradVbias_nul;*/
/*			cout<<"Unbiased simulation"<<endl;*/
/*			break;*/
/*		case harmonic :*/
/*			return 0.5*k_bias*x*x;*/
/*			break;*/
/*		case ABMD :*/
/*			Vbias = Vbias_ABMD;*/
/*			gradVbias = gradVbias_ABMD;*/
/*			cout<<"ABMD bias applied"<<endl;*/
/*			break;*/
/*		case steered :*/
/*			Vbias = Vbias_steered;*/
/*			gradVbias = gradVbias_steered;*/
/*			cout<<"Steered bias applied"<<endl;*/
/*			break;*/
/*		default :*/
/*			cout<<"No bias chosen, default unbiased"<<endl;*/
/*			Vbias = Vbias_nul;*/
/*			gradVbias = gradVbias_nul;*/
/*			break;*/
/*}*/

/*std::vector<biasing_potential> biases;*/

/*for (bias_type = 0; bias_type < n_bias_types; bias_type++) {*/
/*	biases.push_back(biasing_potential<bias_type>);*/
/*}*/

/*biases.push_back(biasing_potential<0>);*/
/*/*biases.push_back(biasing_potential<1>);*/
/*/*biases.push_back(biasing_potential<2>);*/
/*/*biases.push_back(biasing_potential<3>);*/


/*class potential {*/
/*	virtual double V(double x, double t);*/
/*	virtual double gradV(double x, double t);*/
/*}*/

/*template class<bias_type_t bias_type> class biasing_potential public potential {*/
/*	public:*/
/*	virtual double V(double x, double t) override;*/
/*	virtual double gradV(double x, double t) override;*/
/*}*/


/*class total_potential public potential {*/
/*	public:*/
/*	virtual double V(double x, double t) override;*/
/*	virtual double gradV(double x, double t) override;*/
/*	*/
/*	potential system_pot;*/
/*	biasing_potential bias_pot;*/
/*}*/
/*//*/

/*total_potential::V(double x, double t) {*/
/*	return system_pot.V(x, t) + bias_pot.V(x, t);*/
/*}*/

/*//*/
/*class double_well public potential {*/

/*}*/

/*class SMD public potential {*/

/*}*/



// ~~~~~~~~~ Unbiased potentials ~~~~~~~~~ //

//Harmonic potential function
double V_harm(double x, double /* t */);
double gradV_harm(double x, double /* t */);
// Double well potential
double V_dblwl(double x, double t);
double gradV_dblwl(double x, double t);



// ~~~~~~~~~ Constants biases ~~~~~~~~~ //


// No bias
double Vbias_nul(double /* x */, double /* t */);
double gradVbias_nul(double /* x */, double /* t */);

// constant bias
double Vbias_const(double x, double /* t */);
double gradVbias_const(double /* x , double /* t */);

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


/*
//Harmonic potential function
double V_harm(double x);
double gradV_harm(double x);

// Double well potential
double V_dblwl(double x);
double gradV_dblwl(double x);
*/

#endif
