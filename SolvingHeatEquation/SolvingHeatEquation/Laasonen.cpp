#include "laasonen.h"

//CONSTRUCTORS
/*
* Default constructor
*/
Laasonen::Laasonen() {}

/*
* Alternate constructor - creates Laasonen method and compute the r value of the scheme
*/
Laasonen::Laasonen(Parameters parameters, double deltaT) : ImplicitSchemes() {
	r = parameters.getDiffusivity() * (deltaT / pow(parameters.getDeltaX(), 2));
}

// OVERRIDDEN FUNCTION TO GET THE NAME OF THE SCHEME AT RUNTIME 
/*
* @return the name of the scheme
*/
std::string Laasonen::schemeName() {
	return "Laasonen";
}
