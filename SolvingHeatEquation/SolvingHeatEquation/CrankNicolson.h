#ifndef CRANKNICOLSON_H // include guard
#define CRANKNICOLSON_H
#include "implicitSchemes.h"

class CrankNicolson : public ImplicitSchemes {
protected:

public:
	CrankNicolson();
	CrankNicolson(Parameters parameters, double deltaT);

	// Compute RHS of CrankNicolson scheme
	virtual std::vector<double> computeRHS(std::vector<double>& RHS);
	virtual std::string schemeName();
};
#endif