#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "crankNicolson.h"

using namespace std;

//CONSTRUCTORS
/*
* Default constructor - that inherits from the ImplicitSchemes default constractor, @see ImplicitSchemes
*/
CrankNicolson::CrankNicolson(Parameters parameters, int indexDeltaT) : ImplicitSchemes(parameters) {
	r = parameters.getDiffusivity() * (parameters.getVecDeltaT()[indexDeltaT] / (2 * pow(parameters.getDeltaX(), 2)));
}

vector <double> CrankNicolson::computeRHS(vector<double>& RHS)
{
	ImplicitSchemes::computeRHS(RHS);
	vector<double> temp = RHS;
	for (int i = 1; i < temp.size() - 1; i++)
	{
		temp[i] = (1 - 2 * r) * RHS[i] + r * RHS[i + 1] + r * RHS[i - 1];

	}
	return temp;
}

std::string CrankNicolson::SchemeName() {
	std::string str = "CrankNicolson";
	return str;
}