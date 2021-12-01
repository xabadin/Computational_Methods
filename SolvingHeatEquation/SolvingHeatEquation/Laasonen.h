#ifndef LAASONEN_H // include guard
#define LAASONEN_H
#include <cmath>
#include<string>
#include "implicitSchemes.h"

class Laasonen : public ImplicitSchemes {
protected:

public:
	// Constructor
	Laasonen();

	Laasonen(Parameters parameters, double deltaT);
  
	virtual std::string schemeName();
};
#endif