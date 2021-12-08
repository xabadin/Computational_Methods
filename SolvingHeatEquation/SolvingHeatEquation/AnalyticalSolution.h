#ifndef ANALYTICALSOLUTION_H// include guard
#define ANALYTICALSOLUTION_H
#include"Parameters.h"
#include <vector>
#include <fstream>
#include <cmath>

class AnalyticalSolution {
private:
	// Number of the iterations for the Analytical solution
	const int iterations = 10000;
	// Vector of result of the Analytical solution
	std::vector<double> AnalyticalResults;

public:
	// Default constructor
	AnalyticalSolution();
	// Alternate Constructor with parameters
	AnalyticalSolution(Parameters parameters);
	// Function that computes the analytical solution
	std::vector<double> ComputeAnalyticalSolution(Parameters parameters, const double time);
};
#endif