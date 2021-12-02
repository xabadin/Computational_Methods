#include "implicitSchemes.h"

// CONSTRUCTORS
/*
 * Default constructor - initialise the data members
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
	unsigned int n = d.size();

	/*
	* set the system matrix by the given diagonals vectors of the implicit schemes
	* lowerDiagonal and upperDiagonal vectors each have the size of (n-1)
	* and mainDiagonal has the size n 
	* @see report for more explanations regarding the differents size of the vectors
	*/
	std::vector<double> botDiagonal = lowerDiagonal;
	std::vector<double> midDiagonal = mainDiagonal;
	std::vector<double> topDiagonal = upperDiagonal;

	/*
	* solutionX is the vector solution of the unknowns x to calculate in the system A * x = d
	* solutionX vector has the size n
	*/
	std::vector<double> solutionX(n, 0);

	/*
	* @param denominator is a common denominator to calculate values of the vectors topDiagonal and d
	*/
	double denominator {1.0};

	/*
	* brief Thomas Algorithm solve the system matrix in two steps
	* @see the report for detailed explanation how the algorithm works
	*/
	/*
	* Forward elimination step
	*/
	for (int i = 0; i < n - 1; i++) {
		if (i == 0) {
			topDiagonal[0] /= midDiagonal[0];
			d[0] /= midDiagonal[0];
		}
		else {
			denominator = (1.0) / (midDiagonal[i] - (botDiagonal[i] * topDiagonal[i-1]));
			topDiagonal[i] *= denominator;
			d[i] = (d[i] - (botDiagonal[i] * d[i-1])) * denominator;
		}
	}
	
	/*
	* Backward substitution step
	*/
	solutionX[n-1] = d[n-1];
	for (int i = n - 2; i >= 0; i--) {
		solutionX[i] = d[i] - topDiagonal[i] * solutionX[i+1];
	}

	// @result return the solution x
	return solutionX;
}

// SOLVE THE IMPLICIT SCHEMES - LAASONEN AND CRANK-NICHOLSON
/*
* Implement solve function that solve the implicit schemes
* brief solve 1D heat transfer equation using implicit schemes leads to a tridiagonal system A * x = d
* This function is commun for both Laasonen and Crank-Nicholson (Crank-Nicholson RHS is the only difference between the two schemes)
*/
std::vector<std::vector<double>> ImplicitSchemes::solve(Parameters parameters, int indexDeltaT)
{
	std::clock_t start = clock();

	/*
	* Initialize the first element of the right hand side vector d, of the system A * x = d,
	* to the left side surface temperature of the wall, which is part of the boundary conditions
	*/
	wallTemperature.push_back(parameters.getSurfaceTemp());

	/*
	* Setting the values of the diagonals of the implicit schemes system matrix
	* As explained in the report, the upper and lower diagonals set to (-a), whereas the main diagonal set to (1 + (2 * a))
	* @see report for details explanation
	*/
	for (int i = 1; i < parameters.getSpacePoints() - 1; i++) {
		lowerDiagonal.push_back(-r);
		mainDiagonal.push_back(1 + (2 * r));
		upperDiagonal.push_back(-r);
		wallTemperature.push_back(parameters.getInitialTemp());
	}

	/* 
	* Set the first values of upperDiagonal and mainDiagonal, the first value of lowerDiagonal does not exist
	*/
	upperDiagonal.push_back(0);
	mainDiagonal.push_back(1);

	/*
	* Initialize the last element of the right hand side vector d, of the system A*x = d,
	* to the right side surface temperature of the wall, which is part of the boundary conditions
	*/
	wallTemperature.push_back(parameters.getSurfaceTemp());

	/*
	* Solve the tridiagonal system of the implicit schemes using Thomas Algorithm, @see Thomas Algorithm
	* @return schemeSolutions
	*/
	for (int t = 0; t < parameters.getVecTimePoints()[indexDeltaT]; t++) {
		// Puts the solutions in schemeSolutions 
		// It only works if the outputs are equally spaced
		if (t % ((parameters.getVecTimePoints()[indexDeltaT]) / parameters.getVecOutputTimePoints().size()) == 0) {
			schemeSolutions.push_back(wallTemperature);
		}
		// Compute the RHS of Crank-Nicholson scheme
		wallTemperature = computeRHS(wallTemperature);

		// Get the temperature
		wallTemperature = thomasAlgorithm(wallTemperature);
	}
	clock_t end = clock();

	// Set the time of the computation
	setComputationalTime(1000.0 * ((double)end - (double)start) / (double)CLOCKS_PER_SEC);

	// @return the solution of the scheme schemeSolutions
	return schemeSolutions;
}

/*
* @return RHS vector of Crank-Nicholson scheme
*/
std::vector<double> ImplicitSchemes::computeRHS(std::vector<double>& RHS)
{
	return RHS;
}

// ACCESSOR METHODS
/*
* Set the computational time for the scheme
*/
void ImplicitSchemes::setComputationalTime(double time) {
	(*this).computationalTime = time;
}

/*
* Return the computational time for the scheme
*/
double ImplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}
