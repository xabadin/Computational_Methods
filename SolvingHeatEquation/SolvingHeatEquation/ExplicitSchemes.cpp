#include "ExplicitSchemes.h"
#include<iostream>
#include<fstream>
#include<ctime>
#include<cmath>

ExplicitSchemes::ExplicitSchemes() {
	computationalTime = 0;
} //Default constructor

//Need to change variable names here
ExplicitSchemes::ExplicitSchemes(Parameters parameters) {
	this->v2 = std::vector<double>(parameters.getSpacePoints());
	this->v1 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v0 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());

	int computationalTime = 0;
} //Constructor with parameters


std::vector<std::vector<double>> ExplicitSchemes::solve(Parameters parameters, double DeltaT, int meshsize_t) {
	// passer le deltaT dans le constructeur
	std::clock_t start;
	start = std::clock();
	std::vector<std::vector<double>> schemeSolutions;
	int compt = 0;

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
		if (n%10 == 0) {	
			schemeSolutions.push_back(v2);
		}

		if (n < meshsize_t) {
			v0 = v1;
			v1 = v2;
		}
	}
	int computtime = std::clock() - start;
	setComputationalTime(computtime);
	return schemeSolutions;
}

void ExplicitSchemes::setComputationalTime(int time) {
	(*this).computationalTime = time;
}

double ExplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}