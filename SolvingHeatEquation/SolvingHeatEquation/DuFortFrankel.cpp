#include"DuFortFrankel.h"

//Constructor
DuFortFrankel::DuFortFrankel() {};

DuFortFrankel::DuFortFrankel(Parameters parameters) : ExplicitSchemes(parameters) {};

double DuFortFrankel::NextTimeStep(Parameters parameters, int i, double DeltaT) {
	double r = (parameters.getDiffusivity() * DeltaT) / pow(parameters.getDeltaX(), 2);
	return (1 / (1 + 2 * r)) * (v0[i] + 2 * r * (v1[i + 1] - v0[i] + v1[i - 1]));
}

std::string DuFortFrankel::SchemeName() {
	std::string str = "DuFortFrankel";
	return str;
}

