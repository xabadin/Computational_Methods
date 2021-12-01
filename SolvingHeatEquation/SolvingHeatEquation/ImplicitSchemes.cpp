#include "implicitSchemes.h"

// CONSTRUCTORS
/*
 * Default constructor - creates implicit schemes with the given parameters
 * and set the first values of the diagonal vectors
 */
ImplicitSchemes::ImplicitSchemes() {
	this->lowerDiagonal.push_back(0);
	this->mainDiagonal.push_back(1);
	this->upperDiagonal.push_back(0);
	this->schemeSolutions = {};
	this->r = 0;
	this->computationalTime = 0;
};

// SOLVE TRIDIAGONAL SYSTEM A * x = d
/*
* Implement Thomas Algorithm to solve the tri-diagonal system A * x = d of the implicit schemes
*/
std::vector<double> ImplicitSchemes::thomasAlgorithm(std::vector<double> d) {
	/*
	* @param n is the size of the RHS vector d in the tri-diagonal system A * x = d
	*/
	int n = d.size();

	/*
	* set the system matrix by the given diagonals vectors of the implicit schemes
	*/
	std::vector<double> botDiagonal = lowerDiagonal;
	std::vector<double> midDiagonal = mainDiagonal;
	std::vector<double> topDiagonal = upperDiagonal;

	/*
	* solutionX is the vector solution of the unknowns x to calculate in the system A * x = d
	*/
	std::vector<double> solutionX(n, 0);

	/*
	* @param denominator is a common denominator to calculate values of the vectors topDiagonal and d
	*/
	double denominator;

	/*
	* brief Thomas Algorithm solve the system matrix in two steps
	* @see the report for detailed explanation how the algorithm works
	*/
	/*
	* forward elimination step
	*/
	for (int i = 0; i < n - 1; i++) {
		if (i == 0) {
			topDiagonal[0] /= midDiagonal[0];
			d[0] /= midDiagonal[0];
		}
		else {
			denominator = 1.0 / (midDiagonal[i] - (botDiagonal[i] * topDiagonal[i - 1]));
			topDiagonal[i] *= denominator;
			d[i] = (d[i] - (botDiagonal[i] * d[i - 1])) * denominator;
		}
	}

	/*
	* backward substitution step
	*/
	solutionX[n - 1] = d[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		solutionX[i] = d[i] - topDiagonal[i] * solutionX[i + 1];
	}

	return solutionX;
}

std::vector<std::vector<double>> ImplicitSchemes::solve(Parameters parameters, int indexDeltaT)
{
	std::clock_t start = clock();
	
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
		wallTemperature = thomasAlgorithm(wallTemperature);
	}
	clock_t end = clock();
	setComputationalTime(1000.0 * ((double)end - (double)start) / (double)CLOCKS_PER_SEC);
	return schemeSolutions;
}

std::vector<double> ImplicitSchemes::computeRHS(std::vector<double> &RHS) 
{
	return RHS;
}

void ImplicitSchemes::setComputationalTime(double time) {
	(*this).computationalTime = time;
}

double ImplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}

