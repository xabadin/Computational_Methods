#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "laasonen.h"

using namespace std;

//CONSTRUCTORS
/*
* Default constructor - that inherits from the ImplicitSchemes default constractor, @see ImplicitSchemes
*/
Laasonen::Laasonen(Parameters parameters, int indexDeltaT) : ImplicitSchemes(parameters, indexDeltaT) {}


// PRINT RESULTS
/*
* Print the results of Laasonen scheme in .csv file
*/
void Laasonen::printLaasonen(Parameters parameters, int indexDeltaT) {
	vector<double> vectResult = solve(parameters, indexDeltaT);
	ofstream resultsFile("laasonen.csv");
	if (resultsFile.is_open()) {

		for (unsigned i = 0; i < vectResult.size(); i++) {
			resultsFile << (i * parameters.getDeltaX()) << ";" << vectResult[i] << endl;
		}
		resultsFile.close();
	}
}
