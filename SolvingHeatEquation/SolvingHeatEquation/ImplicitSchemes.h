#ifndef IMPLICITSCHEMES_H // include guard
#define IMPLICITSCHEMES_H
#include <iostream>
#include <vector>
#include "parameters.h"

using namespace std;

class ImplicitSchemes {
protected:
	// Vectors of the tridiagonal matrix upper, middle and lower diagonals respectively
	vector<double>  upperDiagonal, mainDiagonal, lowerDiagonal;
	// Right hand side vector, that takes the boundary condition
	vector<double> temperature;
	// @param a is the constant of the 1D heat partial differential equation
	double a;
public:
	// Default contructor

	ImplicitSchemes(Parameters parameters, int indexDeltaT);

	vector<double> solve(Parameters parameters, int indexDeltaT);

	// Thomas Algorithm for solving the tridiagonal system A * x = d
	vector<double> thomasAlgorithm(vector<double> topDiagonal, vector<double> midDiagonal, vector<double> botDiagonal, vector<double> d);

	virtual vector<double> computeRHS(vector<double> &temperature);
	std::string virtual SchemeName() = 0;
};
#endif