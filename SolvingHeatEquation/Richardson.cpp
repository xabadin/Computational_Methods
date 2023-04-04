#include "Richardson.h"
#include <cmath>

//CONSTRUCTORS
/*
* Default constructor
*/
Richardson::Richardson() {};

/*
* Alternate constructor - creates Richardson method
*/
Richardson::Richardson(Parameters parameters) : ExplicitSchemes(parameters) {}
/*
* Compute Richardson solution
*/
double Richardson::NextTimeStep(Parameters parameters, int i, double DeltaT) {
	double r = (parameters.getDiffusivity() * DeltaT) / pow(parameters.getDeltaX(), 2);
	return (2 * r * (v1[i + 1] - (2 * v1[i]) + v1[i - 1])) + v0[i];
	//return 0.1;
}
/*
* Compute FTCS solution
*/
double Richardson::getTimeStep1(Parameters parameters, int i, double DeltaT) {
	double r = (parameters.getDiffusivity() * DeltaT) / pow(parameters.getDeltaX(), 2);
	return v0[i] + r * (v0[i + 1] - 2 * v0[i] + v0[i - 1]);
}
// OVERRIDDEN FUNCTION TO GET THE NAME OF THE SCHEME AT RUNTIME 
/*
* @return the name of the scheme
*/
std::string Richardson::schemeName() {
	return "Richardson";
}