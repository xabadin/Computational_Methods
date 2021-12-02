#define _USE_MATH_DEFINES
#include "AnalyticalSolution.h"

//CONSTRUCTORS
/*
* Default constructor
*/
AnalyticalSolution::AnalyticalSolution() {};

/*
* Alternate constructor - creates the Analytical solution
*/
AnalyticalSolution::AnalyticalSolution(Parameters parameters)
{
	(*this).AnalyticalResults = std::vector<double>(parameters.getSpacePoints());
}

// COMPUTE THE ANALYTICAL SOLUTION
/*
* Compute the Analytical solution for 10000 iterations
*/
std::vector<double> AnalyticalSolution::ComputeAnalyticalSolution(Parameters parameters, const double time)
{
	double sum = 0;
	for (int i = 0; i < parameters.getSpacePoints(); i++) {
		for (int j = 1; j < iterations; j++) {
			sum += exp((-1) * (parameters.getDiffusivity()) * pow(((j * M_PI) / (parameters.getLength())), 2) * (time)) * ((1 - pow(-1, j)) / (j * M_PI)) * sin((j * M_PI * (i * parameters.getDeltaX())) / (parameters.getLength()));
		}
		AnalyticalResults[i] = parameters.getSurfaceTemp() + 2 * (parameters.getInitialTemp() - parameters.getSurfaceTemp()) * sum;
		sum = 0;
	}
	// @return the result of the Analytical solution
	return AnalyticalResults;
}
