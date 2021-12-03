#include "ExplicitSchemes.h"
#include<fstream>
#include<iostream>

ExplicitSchemes::ExplicitSchemes() {
	this->computationalTime = 0;
} //Default constructor

//Need to change variable names here
ExplicitSchemes::ExplicitSchemes(Parameters parameters) {
	this->v2 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v1 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v0 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());

	this->computationalTime = 0;
} //Constructor with parameters


std::vector<std::vector<double>> ExplicitSchemes::solve(Parameters parameters, double DeltaT, int meshsize_t) {

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::vector<double>> schemeSolutions;
	std::ofstream ofs(schemeName()+"TESTENTIER.csv");
	ofs << "x;";
	for (double i = 0; i < 0.04; i += 0.001) {
		ofs << i << ";";
	}
	ofs << std::endl;
	for (int n = 0; n < meshsize_t; n++)
	{
		ofs << "t = " << n * DeltaT << " n = " << n << " ;";
		if (n == 0) {
			v0[0] = 300;
			v1[0] = 300;
			v2[0] = 300;
			v0[double(parameters.getSpacePoints() - 1)] = 300;
			v1[double(parameters.getSpacePoints() - 1)] = 300;
			v2[double(parameters.getSpacePoints() - 1)] = 300;
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
		for (int unsigned l = 0; l < v2.size();l++)
		{
			if (n == 0) {
				ofs << v0[l] << ";";
			}
			else if (n == 1) {
				ofs << v1[l] << ";";
			}
			else {
				ofs << v2[l] << ";";
			}
		}
		ofs << std::endl;
		if (n % ((parameters.getVecTimePoints()[0]) / parameters.getVecOutputTimePoints().size()) == 0) {
			std::cout << "n = " << n << std::endl;
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

void ExplicitSchemes::setComputationalTime(double time) {
	(*this).computationalTime = time;
}

double ExplicitSchemes::getComputationalTime() {
	return (*this).computationalTime;
}