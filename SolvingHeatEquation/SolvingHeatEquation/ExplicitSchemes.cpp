#include "ExplicitSchemes.h"

// CONSTRUCTORS
/*
 * Default constructor - initialise the computationalTime
 */
ExplicitSchemes::ExplicitSchemes() {
	this->computationalTime = 0;
}

/*
* Alternate constructor - creates explicit schemes
*/
ExplicitSchemes::ExplicitSchemes(Parameters parameters) {
	this->v2 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v1 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v0 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());

	this->computationalTime = 0;
}

// SOLVE THE EXPLICIT SCHEMES - DUFORT-FRANKEL AND RICHARDSON
/*
* Implement solve function that solve the explicit schemes
*/
std::vector<std::vector<double>> ExplicitSchemes::solve(Parameters parameters, double DeltaT, int meshsize_t) {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<double>> schemeSolutions;

	for (int n = 0; n < meshsize_t; n++)
	{
		if (n == 0) {
		v0[0] = 300;
		v1[0] = 300;
		v2[0] = 300;
		v0[parameters.getSpacePoints() - 1] = 300;
		v1[parameters.getSpacePoints() - 1] = 300;
		v2[parameters.getSpacePoints() - 1] = 300;
		}
		else if (n == 1) {
			for (int i = 0; i < parameters.getSpacePoints(); i++)
			{
				if(i == 0 || i == parameters.getSpacePoints() - 1)
				{
					v1[i] = parameters.getSurfaceTemp();
				}
				else {
					v1[i] = getTimeStep1(parameters, i, DeltaT);

				}
			}
		}
		else {
			for (int i = 0; i < parameters.getSpacePoints(); i++)
			{
				if(i == 0 || i == parameters.getSpacePoints() - 1)
				{
					v2[i] = parameters.getSurfaceTemp();
				}
				else {
					v2[i] = NextTimeStep(parameters, i, DeltaT);

				}
			}
		}

		if (n % ((parameters.getVecTimePoints()[0]) / parameters.getVecOutputTimePoints().size()) == 0) {
			if (n == 0) {
				schemeSolutions.push_back(v0);
			}
			else {
				schemeSolutions.push_back(v2);
			}
		}
		if (n > 1) {
			v0 = v1;
			v1 = v2;
		}

	}	



	auto finish = std::chrono::high_resolution_clock::now();
	setComputationalTime(double(std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count()));
	return schemeSolutions;
}

// ACCESSOR METHODS
/*
* Set the computational time for the scheme
*/
void ExplicitSchemes::setComputationalTime(double time) {
	(*this).computationalTime = time;
}
/*
* Return the computational time for the scheme
*/
double ExplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}