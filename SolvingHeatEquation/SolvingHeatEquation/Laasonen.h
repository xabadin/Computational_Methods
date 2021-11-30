#ifndef LAASONEN_H // include guard
#define LAASONEN_H
#include <cmath>
#include<string>
#include "implicitSchemes.h"

class Laasonen : public ImplicitSchemes {
protected:

public:
	// Constructor
	Laasonen(Parameters parameters, int indexDeltaT);
  
	std::string SchemeName();
};
#endif