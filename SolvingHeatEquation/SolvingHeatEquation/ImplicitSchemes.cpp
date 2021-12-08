#include "implicitSchemes.h"

// CONSTRUCTORS
/*
* Default constructor
*/
ImplicitSchemes::ImplicitSchemes() {
	this->r = 0;
	this->computationalTime = 0;
};

ImplicitSchemes::ImplicitSchemes(Parameters parameters) {
	this->lowerDiagonal.push_back(0);
	this->mainDiagonal.push_back(1);
	this->upperDiagonal.push_back(0);
	this->r = 0;
	this->computationalTime = 0;
}

// SOLVE TRIDIAGONAL SYSTEM A * x = d
/*
* Implement Thomas Algorithm to solve the tri-diagonal system A * x = d of the implicit schemes
*/
std::vector<double> ImplicitSchemes::thomasAlgorithm(std::vector<double> topDiagonal, std::vector<double> midDiagonal, std::vector<double> botDiagonal, std::vector<double> d) {
	/*
	* @param n is the size in the tri-diagonal system A * x = d
	* n is the size of the vector midDiagonal and the right hand side vector d
	* n-1 is the size of the vector topDiagonal and botDiagonal
	*/
	int n = d.size();

	// x is the vector solution of the unknowns to calculate in the tri-diagonal system A * x = d
	std::vector<double> x(n, 0);

	// @param temp is to temporary save the values
	double temp;

	/*
	* brief Thomas Algorithm based on LU decomposition, where the system A*x = d can be re-written as LU = r
	* where L, U are the lower and upper triangular matrices respectively
	* then the system can be solved, first by solving Lp = r for p and then Ux = p for x, which is the solution
	* Forwards steps:
	* Solve the Lp = r, by setting the main diagonal to 1 and lower and upper diagonals to 0
	* @param topDiagonal is the upper diagonal of the matrix
	* @param middiagonal is the main diagonal of the matrix
	* @param botDiagonal is the lower diagonal of the matrix
	*/
	for (int i = 1; i < n - 1; i++) {
		if (i == 0) {
			topDiagonal[0] /= midDiagonal[0];
			d[0] /= midDiagonal[0];
		}
		else {
			temp = 1.0 / (midDiagonal[i] - topDiagonal[i - 1] * botDiagonal[i]);
			topDiagonal[i] *= temp;
			d[i] = (d[i] - d[i - 1] * botDiagonal[i]) * temp;
		}
	}
	x[n - 1] = d[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		x[i] = d[i] - topDiagonal[i] * x[i + 1];
	}
	return x;
}

std::vector<std::vector<double>> ImplicitSchemes::solve(Parameters parameters, int indexDeltaT)
{
	/*
	* brief solve 1D heat equation using Laasonen leads to a tridiagonal system
	* that can be efficiently solve by Thomas Algorithm, @see the implementation of Thomas Algorithm in ImplicitSchemes file
	*/

	/*
	* Initialize the first element of the right hand side vector d, of the system A*x = d
	* to the left side surface temperature of the wall, which is part of the boundary condition
	*/
	wallTemperature.push_back(parameters.getSurfaceTemp());

	/*
	* Setting the value of the diagonals of the Laasonen matrix system
	* as explained in the report, the upper and lower diagonals set to (-a), whereas the main diagonal set to (1 + (2 * a))
	*/
	for (int i = 1; i < parameters.getSpacePoints() - 1; i++) {
		lowerDiagonal.push_back(-r);
		mainDiagonal.push_back(1 + (2 * r));
		upperDiagonal.push_back(-r);
		wallTemperature.push_back(parameters.getInitialTemp());
	}

	upperDiagonal.push_back(0);
	mainDiagonal.push_back(1);

	/*
	* Initialize the last element of the right hand side vector d, of the system A*x = d
	* to the right side surface temperature of the wall, which is part of the boundary condition
	*/
	wallTemperature.push_back(parameters.getSurfaceTemp());

	/*
	* Solve the tridiagonal system using Thomas Algorithm
	* @return schemeSolutions
	*/
	for (int t = 0; t < parameters.getVecTimePoints()[indexDeltaT]; t++) {
		//Puts the solutions in schemeSolutions 
		//It only works if the outputs are equally spaced
		if (t % ((parameters.getVecTimePoints()[indexDeltaT]) / parameters.getVecOutputTimePoints().size()) == 0) {
			schemeSolutions.push_back(wallTemperature);
		}

		wallTemperature = computeRHS(wallTemperature);
		wallTemperature = thomasAlgorithm(lowerDiagonal, mainDiagonal, upperDiagonal, wallTemperature);
	}
	return schemeSolutions;
}

std::vector<double> ImplicitSchemes::computeRHS(std::vector<double> &wallTemperature) 
{
	return wallTemperature;
}

