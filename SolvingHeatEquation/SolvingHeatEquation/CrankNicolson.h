#ifndef CRANKNICOLSON_H // include guard
#define CRANKNICOLSON_H
#include <cmath>
#include<string>
#include "implicitSchemes.h"

class CrankNicolson : public ImplicitSchemes {
protected:
	// Vectors of the tridiagonal matrix upper, middle and lower diagonals respectively
	vector<double>  upperDiagonal, mainDiagonal, lowerDiagonal;

	// Right hand side vector, that takes the boundary condition
	vector<double> temperature;

public:
	CrankNicolson(Parameters parameters, int indexDeltaT);

	// Print the result in a .csv format
	void printCrankNicolson(Parameters paramaters, int indexDeltaT);

	// Compute RHS of CrankNicolson scheme
	virtual vector<double> computeRHS(vector<double>& initialValues);
	std::string SchemeName();
};
#endif