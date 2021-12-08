#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"
#include "DuFortFrankel.h"
#include "Richardson.h"
#include "Printer.h"

int main()
{
	Parameters parameters = Parameters(); //Creation of the parameters object with all the data

	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);
	std::vector<std::vector<double>> analyticalSolutions;

	for (int i = 0; i < parameters.getVecOutputTimePoints().size(); ++i)
	{
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getVecOutputTimePoints()[i]));
	}

	

	DuFortFrankel duFortFrankel = DuFortFrankel(parameters);
	Richardson richardson = Richardson(parameters);

	richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]);
	duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]);

	Printer printer = Printer(analyticalSolutions);

	printer.printAnalytical(parameters);

	//Print Explicit Schemes
	
	
	//Print Implicit Schemes
	for (int indexDeltaT = 0; indexDeltaT < parameters.getVecDeltaT().size(); ++indexDeltaT)
	{
		Laasonen laasonen = Laasonen(parameters, indexDeltaT);
		printer.print(parameters, "laasonen" + std::to_string(parameters.getVecDeltaT()[indexDeltaT]), laasonen.solve(parameters, indexDeltaT));
	}

	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);

	printer.print(parameters, "crankNicolson" + std::to_string(parameters.getVecDeltaT()[0]), crankNicolson.solve(parameters, 0));

	return 0;
} 