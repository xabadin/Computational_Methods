#ifndef LAASONEN_H // include guard
#define LAASONEN_H
#include "implicitSchemes.h"
#include <cmath>
#include <string>

class Laasonen : public ImplicitSchemes 
{
public:
	// Default constructor
	Laasonen();

	// Alternate Constructor with parameters
	Laasonen(Parameters parameters, double deltaT);
  
	// Return the name of the scheme
	virtual std::string schemeName();
};

#endif
