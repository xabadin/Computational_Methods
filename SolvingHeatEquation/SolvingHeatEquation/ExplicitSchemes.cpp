#include "ExplicitSchemes.h"

ExplicitSchemes::ExplicitSchemes() {
	this->computationalTime = 0;
} //Default constructor

//Need to change variable names here
ExplicitSchemes::ExplicitSchemes(Parameters parameters) {
	this->v2 = std::vector<double>(parameters.getSpacePoints());
	this->v1 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v0 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());

	this->computationalTime = 0;
} //Constructor with parameters


std::vector<std::vector<double>> ExplicitSchemes::solve(Parameters parameters, double DeltaT, int meshsize_t) {
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<double>> schemeSolutions;

	for (int n = 0; n < meshsize_t; n++)
	{
		for (int i = 0; i < parameters.getSpacePoints(); i++)
		{
			if (i == 0 || i == parameters.getSpacePoints() - 1)
			{
				v2[i] = parameters.getSurfaceTemp();
			}
			else {
				v2[i] = NextTimeStep(parameters, i, DeltaT);
			}
		}
		//to get only the 0.1's values
		if (n % ((parameters.getVecTimePoints()[0]) / parameters.getVecOutputTimePoints().size()) == 0) {
			schemeSolutions.push_back(v2);
		}
		v0 = v1;
		v1 = v2;
	}
	auto finish = std::chrono::high_resolution_clock::now();
	setComputationalTime(double(std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count()));
	return schemeSolutions;
}

void ExplicitSchemes::setComputationalTime(double time) {
	(*this).computationalTime = time;
}

double ExplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}