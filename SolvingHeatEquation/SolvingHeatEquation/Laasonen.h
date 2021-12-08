#ifndef LAASONEN_H // include guard
#define LAASONEN_H
#include <cmath>
#include<string>
#include "implicitSchemes.h"

class Laasonen : public ImplicitSchemes {
protected:

public:
	// Default constructor
	Laasonen();
	// Alternate Constructor with parameters
	Laasonen(Parameters parameters, double deltaT);
	// Return the name of the scheme
	virtual std::string schemeName();
};
#endif