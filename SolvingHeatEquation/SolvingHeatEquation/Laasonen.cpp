#include "laasonen.h"

using namespace std;

//CONSTRUCTORS
/*
* Default constructor - that inherits from the ImplicitSchemes default constractor, @see ImplicitSchemes
*/
Laasonen::Laasonen(Parameters parameters, int indexDeltaT) : ImplicitSchemes(parameters) {
	r = parameters.getDiffusivity() * (parameters.getVecDeltaT()[indexDeltaT] / pow(parameters.getDeltaX(), 2));
}
