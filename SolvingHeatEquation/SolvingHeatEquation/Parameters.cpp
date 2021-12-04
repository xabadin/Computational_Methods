#include "parameters.h"
//CONSTRUCTORS
/*
* Default constructor - initialise the Heat PDE parameters as given in the problem definition
*/
Parameters::Parameters() {
	(*this).diffusivity = 0.1;
	(*this).deltaX = 0.05;
	(*this).length = 1;
	(*this).spacePoints = 21;
	(*this).surfaceTemp = 300;
	(*this).initialTemp = 100;
	(*this).vecDeltaT = { 0.01,0.025,0.05,0.1 };
	(*this).timePoints = { 51, 21, 11, 6 };
	(*this).outputTimePoints = { 0.1, 0.2, 0.3, 0.4, 0.5 };
}

// ACCESSOR METHODS
/*
* Get method that returns the diffusivity
*/
double Parameters::getDiffusivity() {
	return (*this).diffusivity;
}

/*
* Get method that returns DeltaX
*/
double Parameters::getDeltaX() {
	return (*this).deltaX;
}

/*
* Get method that returns the Length of the wall
*/
double Parameters::getLength() {
	return (*this).length;
}

/*
* Get method that returns the Space Points
*/
int Parameters::getSpacePoints() {
	return (*this).spacePoints;
}

/*
* Get method that returns the Surface Temperature
*/
double Parameters::getSurfaceTemp() {
	return (*this).surfaceTemp;
}

/*
* Get method that returns the Initial Temperature
*/
double Parameters::getInitialTemp() {
	return (*this).initialTemp;
}

/*
* Get method that returns a vector that contains all DeltaT
*/
std::vector<double> Parameters::getVecDeltaT() {
	return (*this).vecDeltaT;
}

/*
* Get method that returns a vector of number of time points according to delta t
*/
std::vector<int> Parameters::getVecTimePoints() {
	return (*this).timePoints;
}

/*
* Get method that returns the Time Points
*/
std::vector<double> Parameters::getVecOutputTimePoints() {
	return (*this).outputTimePoints;
}