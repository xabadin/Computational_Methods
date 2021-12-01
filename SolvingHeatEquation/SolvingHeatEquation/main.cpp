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
	//Initialisation of parameters and analytical solution class
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);

	//Vector in which analyticalSolutions are stored
	std::vector<std::vector<double>> analyticalSolutions;

	//Storing computational times of the different schemes in this vector
	std::vector<std::string> computationalTimeResults;

	//To generate the analytical solutions for the different time points.
	analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, 0.0));
	for (int unsigned i = 0; i < parameters.getVecOutputTimePoints().size(); i++) {
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getVecOutputTimePoints()[i]));
	}

	//Initialisation of the explicit schemes classes
	DuFortFrankel duFortFrankel = DuFortFrankel(parameters);
	Richardson richardson = Richardson(parameters);

	//Initialisatoin of the printer
	Printer printer = Printer(analyticalSolutions);
	
	//Printing the analytical solution
	printer.printAnalytical(parameters);

	//Print the Explicit schemes results and get the computational time in the vector
	//DuFortFrankel
	printer.print(parameters, duFortFrankel.schemeName(), duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(duFortFrankel.schemeName() + ";" + std::to_string(duFortFrankel.getComputationalTime()));
	//Richardson
	printer.print(parameters, richardson.schemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(richardson.schemeName() + ";" + std::to_string(richardson.getComputationalTime()));
	
	//Print the results of the Implicit Schemes and get the respective computationaltime
	//Laasonen in a for loop to compute for the different deltaT
	for (int unsigned indexDeltaT = 0; indexDeltaT < parameters.getVecDeltaT().size(); ++indexDeltaT)
	{
		Laasonen laasonen = Laasonen(parameters, indexDeltaT);
		printer.print(parameters, laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]), laasonen.solve(parameters, indexDeltaT));
		computationalTimeResults.push_back(laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]) + ";" + std::to_string(laasonen.getComputationalTime()));
	}

	//CrankNicolson only with the first deltaT (0.01)
	//It would be nice if 0 had a variable name (firstdeltaT or something like that)
	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);
	printer.print(parameters, crankNicolson.schemeName(), crankNicolson.solve(parameters, 0));
	computationalTimeResults.push_back(crankNicolson.schemeName() + ";" + std::to_string(crankNicolson.getComputationalTime()));

	//Printing the different computational times in a csv file
	printer.printComputationalTime(computationalTimeResults);

	return 0;
}