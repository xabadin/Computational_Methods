#ifndef IMPLICITSCHEMES_H // include guard
#define IMPLICITSCHEMES_H
#include "parameters.h"

class ImplicitSchemes {
protected:
	// Vectors of the tridiagonal matrix upper, middle and lower diagonals respectively
	std::vector<double>  upperDiagonal, mainDiagonal, lowerDiagonal;
	// Right hand side vector, that takes the boundary condition
	std::vector<double> wallTemperature;
	// @param a is the constant of the 1D heat partial differential equation
	double r;
	//computational time of the scheme
	double computationalTime;
	//Used to store the solutions at each OutputTimePoints selected in the parameters class
	std::vector<std::vector<double>> schemeSolutions;
	
public:
	// Default contructor
	ImplicitSchemes();

	ImplicitSchemes(Parameters parameters);

	std::vector<std::vector<double>> solve(Parameters parameters, int indexDeltaT);

	// Thomas Algorithm for solving the tridiagonal system A * x = d
	std::vector<double> thomasAlgorithm(std::vector<double> topDiagonal, std::vector<double> midDiagonal, std::vector<double> botDiagonal, std::vector<double> d);

	virtual std::vector<double> computeRHS(std::vector<double> &RHS);
	std::string virtual SchemeName() = 0;
};
#endif