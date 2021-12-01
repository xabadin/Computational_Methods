#include "laasonen.h"

using namespace std;

//CONSTRUCTORS
/*
* Default constructor - that inherits from the ImplicitSchemes default constractor, @see ImplicitSchemes
*/
Laasonen::Laasonen() {}

Laasonen::Laasonen(Parameters parameters, double deltaT) : ImplicitSchemes() {
	r = parameters.getDiffusivity() * (deltaT / pow(parameters.getDeltaX(), 2));
}

std::string Laasonen::schemeName() {
	return "Laasonen";
}