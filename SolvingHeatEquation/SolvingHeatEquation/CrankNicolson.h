#ifndef CRANKNICOLSON_H // include guard
#define CRANKNICOLSON_H
#include "implicitSchemes.h"

class CrankNicolson : public ImplicitSchemes {
protected:

public:
	CrankNicolson(Parameters parameters, int indexDeltaT);

	// Compute RHS of CrankNicolson scheme
	virtual vector<double> computeRHS(vector<double>& initialValues);
	std::string schemeName();
};
#endif