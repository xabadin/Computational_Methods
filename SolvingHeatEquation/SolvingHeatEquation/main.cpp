#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"
#include "DuFortFrankel.h"
#include "Richardson.h"

int main()
{
	Parameters parameters = Parameters(); //Creation of the parameters object with all the data

	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);
	std::vector<std::vector<double>> analyticalSolutions;

	for (int i = 0; i < parameters.getOutputTimePoints().size(); ++i)
	{
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getOutputTimePoints()[i]));
	}

	Laasonen laasonen = Laasonen(parameters, 0);
	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);

	DuFortFrankel duFortFrankel = DuFortFrankel(parameters);
	Richardson richardson = Richardson(parameters);

	richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]);
	duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]);

	//Need to change this into a printer
	laasonen.printLaasonen(parameters, 0);
	crankNicolson.printCrankNicolson(parameters, 0);

	return 0;
} 