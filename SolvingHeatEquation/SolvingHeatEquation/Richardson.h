#ifndef RICHARDSON_H // include guard
#define RICHARDSON_H
#include"ExplicitSchemes.h"
#include<string>

class Richardson : public ExplicitSchemes 
{
public:
	// Default constructor
	Richardson(); 

	// Alternate Constructor with parameters
	Richardson(Parameters parameters); 

	// Compute the result using v0 <=> (n-1) and v1 <=> (n) values to find v2 <=> (n+1) values
	double NextTimeStep(Parameters parameters, int i, double DeltaT);

	// Return the name of the scheme
	std::string schemeName(); 
};

#endif
