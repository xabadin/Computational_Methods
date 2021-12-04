#pragma once
#ifndef DUFORTFRANKEL_H// include guard
#define DUFORTFRANKEL_H

#include"ExplicitSchemes.h"
#include<string>

class DuFortFrankel : public ExplicitSchemes {
public:
	// Default constructor
	DuFortFrankel(); 
	// Alternate Constructor with parameters
	DuFortFrankel(Parameters parameters); 
	// Compute the result using  v0 <=> (n-1) and v1 <=> (n) values to find v2 <=> (n+1) values
	double NextTimeStep(Parameters parameters, int i, double DeltaT);
	// Compute the result using  v0 <=> (n) to find v1 <=> (n+1) values
	double getTimeStep1(Parameters parameters, int i, double DeltaT);
	// Return the name of the scheme
	std::string schemeName(); 

};
#endif
