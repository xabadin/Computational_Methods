#ifndef EXPLICITSCHEMES_H // include guard
#define EXPLICITSCHEMES_H
#include"Parameters.h"
#include<string>
#include<chrono>

class ExplicitSchemes
{
protected:
	std::vector<double> v2; //n+1 values
	std::vector<double> v1; //n values
	std::vector<double> v0; //n-1 values

	double computationalTime;

public:
	// Default constructor
	ExplicitSchemes();
	// Alternate Constructor with parameters
	ExplicitSchemes(Parameters parameters); 
	// Solve solution for the explicit schemes
	std::vector<std::vector<double>> solve(Parameters parameters, double DeltaT, int timePoints);
	// Function to get the next time step
	virtual double  NextTimeStep(Parameters parameters, int i, double DeltaT) = 0;
	// Function to get the time step 1 using FTCS
	double virtual getTimeStep1(Parameters parameters, int i, double DeltaT) = 0;
	// Overridden function that returns the name of a given scheme
	virtual std::string  schemeName() = 0;
	// ACCESSOR METHODS
	double getComputationalTime();
	void setComputationalTime(double time);
};
#endif