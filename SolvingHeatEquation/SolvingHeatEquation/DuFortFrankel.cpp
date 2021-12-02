#include"DuFortFrankel.h"

//CONSTRUCTORS
/*
* Default constructor
*/
DuFortFrankel::DuFortFrankel() {};

/*
* Alternate constructor - creates DuFort-Frankel method
*/
DuFortFrankel::DuFortFrankel(Parameters parameters) : ExplicitSchemes(parameters) {};

/*
* Compute DuFort-Frankel solution
*/
double DuFortFrankel::NextTimeStep(Parameters parameters, int i, double DeltaT) {
	double r = (parameters.getDiffusivity() * DeltaT) / pow(parameters.getDeltaX(), 2);
	return (1 / (1 + 2 * r)) * (v0[i] + 2 * r * (v1[(double)i + 1] - v0[i] + v1[(double)i - 1]));
}

// OVERRIDDEN FUNCTION TO GET THE NAME OF THE SCHEME AT RUNTIME 
/*
* @return the name of the scheme
*/
std::string DuFortFrankel::schemeName() {
	return "DuFortFrankel";
}
