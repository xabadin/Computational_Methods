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
CrankNicolson::CrankNicolson() {}

/*
* Alternate constructor - creates Crank-Nicholson method and compute the r value of the scheme
*/
CrankNicolson::CrankNicolson(Parameters parameters, double deltaT) : ImplicitSchemes() {
	r = parameters.getDiffusivity() * (deltaT / (2 * pow(parameters.getDeltaX(), 2)));
}

// RHS COMPUTATION
/*
* @return the RHS vector of Crank-Nicholson
*/
vector <double> CrankNicolson::computeRHS(vector<double>& RHS)
{
	ImplicitSchemes::computeRHS(RHS);
	vector<double> temp = RHS;
	for (int unsigned i = 1; i < temp.size() - 1; i++)
	{
		temp[i] = (1 - 2 * r) * RHS[i] + r * RHS[i + 1] + r * RHS[i - 1];

	}
	return temp;
}

// OVERRIDDEN FUNCTION TO GET THE NAME OF THE SCHEME AT RUNTIME 
/*
* @return the name of the scheme
*/
std::string CrankNicolson::schemeName() {
	return "CrankNicolson";
}