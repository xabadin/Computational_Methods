#include "parameters.h"

Parameters::Parameters() {
	(*this).diffusivity = 0.1;
	(*this).deltaX = 0.05;
	(*this).length = 1;
	(*this).spacePoints = 21;
	(*this).surfaceTemp = 300;
	(*this).initialTemp = 100;
	(*this).vecDeltaT = { 0.01,0.025,0.05,0.1 };
	(*this).timePoints = { 50, 20, 10, 5 };
	(*this).outputTimePoints = { 0.1, 0.2, 0.3, 0.4, 0.5 };
}

double Parameters::getDiffusivity() {
	return (*this).diffusivity;
}
double Parameters::getDeltaX() {
	return (*this).deltaX;
}
double Parameters::getLength() {
	return (*this).length;
}
int Parameters::getSpacePoints() {
	return (*this).spacePoints;
}
double Parameters::getSurfaceTemp() {
	return (*this).surfaceTemp;
}
double Parameters::getInitialTemp() {
	return (*this).initialTemp;
}
std::vector<double> Parameters::getVecDeltaT() {
	return (*this).vecDeltaT;
}
std::vector<int> Parameters::getVecTimePoints() {
	return (*this).timePoints;
}
std::vector<double> Parameters::getVecOutputTimePoints() {
	return (*this).outputTimePoints;
}