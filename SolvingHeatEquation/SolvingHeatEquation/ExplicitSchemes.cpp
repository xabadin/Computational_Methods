#include "ExplicitSchemes.h"

ExplicitSchemes::ExplicitSchemes() {} //Default constructor

//Need to change variable names here
ExplicitSchemes::ExplicitSchemes(Parameters parameters) {
	this->v2 = std::vector<double>(parameters.getSpacePoints());
	this->v1 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
	this->v0 = std::vector<double>(parameters.getSpacePoints(), parameters.getInitialTemp());
} //Constructor with parameters


void ExplicitSchemes::solve(Parameters parameters, double DeltaT, int meshsize_t) {

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

		//On remplace tt les vecteur, cad v0=v1 puis v1=v2 et on recalcule v2 en boucle
		if (n < meshsize_t) {
			v0 = v1;
			v1 = v2;
		}
	}
}