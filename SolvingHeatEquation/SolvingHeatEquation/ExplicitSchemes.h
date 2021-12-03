#ifndef EXPLICITSCHEMES_H
#define EXPLICITSCHEMES_H
#include"Parameters.h"
#include<string>
#include<chrono>

class ExplicitSchemes
{
protected:
	std::vector<double> v2; //N+1 values
	std::vector<double> v1; //N values
	std::vector<double> v0; //N-1 values

	double computationalTime;

public:
	ExplicitSchemes(); //Default constructor
	ExplicitSchemes(Parameters parameters); //Constructor with parameters

	std::vector<std::vector<double>> solve(Parameters parameters, double DeltaT, int timePoints); //Solving solution for our explicit schemes

	virtual double  NextTimeStep(Parameters parameters, int i, double DeltaT) = 0;
	double virtual getTimeStep1(Parameters parameters, int i, double DeltaT) = 0;
	virtual std::string  schemeName() = 0;

	double getComputationalTime();
	void setComputationalTime(double time);
};
#endif