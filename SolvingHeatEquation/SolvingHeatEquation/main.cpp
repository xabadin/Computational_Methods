#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"
#include "DuFortFrankel.h"
#include "Richardson.h"
#include "Printer.h"


#include<ctime>
#include<iostream>

int main()
{
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);
  
	//Explicit constructors
	DuFortFrankel duFortFrankel = DuFortFrankel(parameters); //rajouter le indice delta t
	Richardson richardson = Richardson(parameters);

	std::vector<std::vector<double>> analyticalSolutions;
	std::vector<std::string> computationalTimeResults;

	//To generate the analytical solutions for the 5 time points.
	analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, 0.0));
	for (int unsigned i = 0; i < parameters.getVecOutputTimePoints().size(); i++) {
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getVecOutputTimePoints()[i]));
	}

	Printer printer = Printer(analyticalSolutions);
	printer.printAnalytical(parameters);

	//Print Explicit and get computational time

	printer.print(parameters, duFortFrankel.schemeName(), duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(duFortFrankel.schemeName() + ";" + std::to_string(duFortFrankel.getComputationalTime()));

	printer.print(parameters, richardson.schemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(richardson.schemeName() + ";" + std::to_string(richardson.getComputationalTime()));
	
	
	//Print Implicit Schemes and get computationaltime
	for (int unsigned indexDeltaT = 0; indexDeltaT < parameters.getVecDeltaT().size(); ++indexDeltaT)
	{
		Laasonen laasonen = Laasonen(parameters, indexDeltaT);
		printer.print(parameters, laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]), laasonen.solve(parameters, indexDeltaT));
		computationalTimeResults.push_back(laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]) + ";" + std::to_string(laasonen.getComputationalTime()));
	}

	//It would be nice if 0 add a variable name (firstdeltaT or something like that)
	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);
	printer.print(parameters, crankNicolson.schemeName(), crankNicolson.solve(parameters, 0));
	computationalTimeResults.push_back(crankNicolson.schemeName() + ";" + std::to_string(crankNicolson.getComputationalTime()));

	printer.printComputationalTime(computationalTimeResults);

	return 0;
}