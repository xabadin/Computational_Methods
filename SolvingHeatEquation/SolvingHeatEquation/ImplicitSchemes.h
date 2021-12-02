#ifndef IMPLICITSCHEMES_H // include guard
#define IMPLICITSCHEMES_H
#include "parameters.h"
#include <ctime>
#include <string>

class ImplicitSchemes 
{
protected:
	// Vectors of the tridiagonal matrix lower, middle and upper diagonals respectively
	std::vector<double>  lowerDiagonal, mainDiagonal, upperDiagonal;

	// Right hand side vector, that takes the boundary conditions
	std::vector<double> wallTemperature;

	// @param r is the constant of the 1D heat partial differential equation and differs from scheme to another
	double r;

	// Computational time of the scheme
	double computationalTime;

	// Vector to store the solutions at each OutputTimePoints selected in the parameters. @see parameters class
	std::vector<std::vector<double>> schemeSolutions;
	
public:
	// Default contructor
	ImplicitSchemes();

	// Solve the implicit schemes and is commun to both the implicit schemes studied
	std::vector<std::vector<double>> solve(Parameters parameters, int indexDeltaT);

	// Thomas Algorithm method
	std::vector<double> thomasAlgorithm(std::vector<double> d);

	// Used to compute the RHS of Crank-Nicholson scheme, @see report for more details
	virtual std::vector<double> computeRHS(std::vector<double> &RHS);

	// Overridden function that returns the name of a given scheme
	virtual std::string schemeName() = 0;

	// ACCESSOR METHODS
	double getComputationalTime();
	void setComputationalTime(double time);
};

#endif
