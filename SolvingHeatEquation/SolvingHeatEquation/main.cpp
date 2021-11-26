#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"

int main()
{
	Parameters parameters = Parameters(); //Creation of the parameters object with all the data
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);

	std::vector<std::vector<double>> analyticalSolutions;

	Laasonen laasonen = Laasonen(parameters, 0);
	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);

	//Need to change this into a printer
	laasonen.printLaasonen(parameters, 0);
	crankNicolson.printCrankNicolson(parameters, 0);

	return 0;
}