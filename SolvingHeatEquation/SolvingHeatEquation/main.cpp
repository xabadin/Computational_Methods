#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"
#include "DuFortFrankel.h"
#include "Richardson.h"
#include "ExplicitSchemes.h"
#include "Printer.h"

#include<iostream>
#include<vector>
#include<fstream>
#include<string>

int main()
{
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);

	//Explicit constructors
	DuFortFrankel dufort = DuFortFrankel(parameters); //rajouter le indice delta t
	Richardson richardson = Richardson(parameters);

	//Implicit constructors
	Laasonen laasonen = Laasonen(parameters, 0);
	CrankNicolson crankNicolson = CrankNicolson(parameters, 0);


	std::vector<std::vector<double>> analyticalSolutions;
	std::vector<std::string> computationalTimeResults;

	//To generate the analytical solutions for the 5 time points.
	for (int unsigned i = 0; i < parameters.getOutputTimePoints().size(); i++) {
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getOutputTimePoints()[i]));
	}

	Printer printer = Printer(parameters, analyticalSolutions);
	printer.printAnalytical(parameters);

	//Print Explicit
	printer.print(parameters, dufort.SchemeName(), dufort.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]));
	printer.print(parameters, richardson.SchemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getTimePoints()[0]));

	//Implicit
	crankNicolson.printCrankNicolson(parameters, 0);
	laasonen.printLaasonen(parameters, 0);

	//Computational time explicit
	computationalTimeResults.push_back(dufort.SchemeName() + ";" + to_string(dufort.getComputationalTime()));
	computationalTimeResults.push_back(richardson.SchemeName() + ";" + to_string(richardson.getComputationalTime()));



	printer.printComputationalTime(computationalTimeResults);




	//for (int unsigned i = 0; i < parameters.getVecDeltaT().size(); i++) {
	//	laasonen.printLaasonen(parameters, i);
	//}
	//

	/*for (int unsigned x = 0; x < 2; x++) {
		std::cout << computationalTimeResults[x] << std::endl;
	}*/

	return 0;
}