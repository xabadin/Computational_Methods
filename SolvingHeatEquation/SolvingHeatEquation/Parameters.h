#ifndef PARAMETERS_H
#define PARAMETERS_H 

#include<vector>

class Parameters
{
private:

	double diffusivity = 0.1; // 0.1 ft^2/hr
	double deltaX; // 0.05
	double length; // 1 ft
	int spacePoints;// = int((length / deltaX) + 0.5); // 40
	double surfaceTemp; // 300
	double initialTemp; // 100

	std::vector<double> vecDeltaT; // 
	std::vector<int> timePoints; // 0, 0.5
	std::vector<double> outputTimePoints; // 0.1 - 0.2 - 0.3 - 0.4 - 0.5

public:
	Parameters(); //default constructor

	double getDiffusivity();
	double getDeltaX();
	double getLength();
	int getSpacePoints();
	double getSurfaceTemp();
	double getInitialTemp();
	std::vector<double> getVecDeltaT();
	std::vector<int> getTimePoints();
	std::vector<double> getOutputTimePoints();
};
#endif