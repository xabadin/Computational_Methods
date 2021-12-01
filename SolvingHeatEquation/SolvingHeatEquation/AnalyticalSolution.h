#ifndef ANALYTICALSOLUTION_H
#define ANALYTICALSOLUTION_H
#include"Parameters.h"
#include <vector>
#include <fstream>
#include <cmath>

class AnalyticalSolution {
private:
	const int iterations = 10000;
	std::vector<double> AnalyticalResults;

public:
	AnalyticalSolution();
	AnalyticalSolution(Parameters parameters);

	std::vector<double> ComputeAnalyticalSolution(Parameters parameters, const double time);
};
#endif