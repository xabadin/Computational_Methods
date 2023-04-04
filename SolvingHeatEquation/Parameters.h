#ifndef PARAMETERS_H// include guard
#define PARAMETERS_H 

#include<vector>

class Parameters
{
private:
	// PARAMETERS OF THE HEAT PDE
	double diffusivity = 0.1;  // diffusivity of the heat PDE
	double deltaX; // distance between two adjusant points in the mesh
	double length;// thickness of the wall
	int spacePoints;// the number of space points
	double surfaceTemp; // the surface temperature
	double initialTemp; // the initial temperature
	std::vector<double> vecDeltaT; // vector of delta T values
	std::vector<int> timePoints; // vector of number of time points according to deltaT
	std::vector<double> outputTimePoints; // time points {0.1 - 0.2 - 0.3 - 0.4 - 0.5} in which the results are displayed

public:
	// Default constructor
	Parameters();

	// Accessor methods
	double getDiffusivity();
	double getDeltaX();
	double getLength();
	int getSpacePoints();
	double getSurfaceTemp();
	double getInitialTemp();
	std::vector<double> getVecDeltaT();
	std::vector<int> getVecTimePoints();
	std::vector<double> getVecOutputTimePoints();
};
#endif