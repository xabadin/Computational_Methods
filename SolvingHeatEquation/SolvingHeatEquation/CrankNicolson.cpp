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
CrankNicolson::CrankNicolson(Parameters parameters, int indexDeltaT) : ImplicitSchemes(parameters, indexDeltaT) {
	a = parameters.getDiffusivity() * (parameters.getVecDeltaT()[indexDeltaT] / (2 * pow(parameters.getDeltaX(), 2)));
}

// PRINT RESULTS
/*
* Print the results of CrankNicolson scheme in .csv file
*/
void CrankNicolson::printCrankNicolson(Parameters parameters, int indexDeltaT) {
	vector<double> vectResult = solve(parameters, indexDeltaT);
	ofstream resultsFile("CrankNicolson.csv");
	if (resultsFile.is_open()) {

		for (unsigned i = 0; i < vectResult.size(); i++) {
			resultsFile << (i * parameters.getDeltaX()) << ";" << vectResult[i] << endl;
		}
		resultsFile.close();
	}
}

vector <double> CrankNicolson::computeRHS(vector<double>& temperature)
{
	ImplicitSchemes::computeRHS(temperature);
	vector<double> temp = temperature;
	for (int i = 1; i < temp.size() - 1; i++)
	{
		temp[i] = (1 - 2 * a) * temperature[i] + a * temperature[i + 1] + a * temperature[i - 1];

	}
	return temp;
}