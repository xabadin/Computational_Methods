#include "Richardson.h"

//Constructor
Richardson::Richardson() {};

Richardson::Richardson(Parameters parameters) : ExplicitSchemes(parameters) {} //Constructor with parameters

double Richardson::NextTimeStep(Parameters parameters, int i, double DeltaT) {
	double r = (parameters.getDiffusivity() * DeltaT) / pow(parameters.getDeltaX(), 2);
	return (2 * r * (v1[i + 1] - (2 * v1[i]) + v1[i - 1])) + v0[i];
	//return 0.1;
}

std::string Richardson::schemeName() {
	std::string str = "Richardson";
	return str;
}