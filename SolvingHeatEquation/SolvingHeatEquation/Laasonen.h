#ifndef LAASONEN_H // include guard
#define LAASONEN_H
#include <cmath>
#include "implicitSchemes.h"

class Laasonen : public ImplicitSchemes {
protected:


public:
	// Constructor
	Laasonen(Parameters parameters, int indexDeltaT);

	// Print the result in a .csv format
	void printLaasonen(Parameters paramaters, int indexDeltaT);
};
#endif