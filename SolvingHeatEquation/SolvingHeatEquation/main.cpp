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
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);
  
	//Explicit constructors
	DuFortFrankel dufort = DuFortFrankel(parameters); //rajouter le indice delta t
	Richardson richardson = Richardson(parameters);

	std::vector<std::vector<double>> analyticalSolutions;
	std::vector<std::string> computationalTimeResults;

	//To generate the analytical solutions for the 5 time points.
	for (int unsigned i = 0; i < parameters.getOutputTimePoints().size(); i++) {
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getOutputTimePoints()[i]));
	}

	Printer printer = Printer(analyticalSolutions);
	printer.printAnalytical(parameters);

	//Print Explicit
	printer.print(parameters, dufort.SchemeName(), dufort.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]));
	printer.print(parameters, richardson.SchemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]));

	//Computational time explicit
	computationalTimeResults.push_back(dufort.SchemeName() + ";" + to_string(dufort.getComputationalTime()));
	computationalTimeResults.push_back(richardson.SchemeName() + ";" + to_string(richardson.getComputationalTime()));

	printer.printComputationalTime(computationalTimeResults);
	
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