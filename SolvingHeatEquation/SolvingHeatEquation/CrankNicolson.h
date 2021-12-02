#ifndef CRANKNICOLSON_H // include guard
#define CRANKNICOLSON_H
#include "implicitSchemes.h"

class CrankNicolson : public ImplicitSchemes 
{
public:
	// Default constructor
	CrankNicolson();

	// Alternate Constructor with parameters
	CrankNicolson(Parameters parameters, double deltaT);

	// Compute RHS of CrankNicolson scheme
	virtual std::vector<double> computeRHS(std::vector<double>& RHS);

	// Return the name of the scheme
	virtual std::string schemeName();
};

#endif
