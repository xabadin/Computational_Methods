#include "parameters.h"
#include "AnalyticalSolution.h"
#include "ImplicitSchemes.h"
#include "Laasonen.h"
#include "CrankNicolson.h"
#include "DuFortFrankel.h"
#include "Richardson.h"
#include "Printer.h"

#include<chrono>
#include<iostream>

int main()
{
	//Initialisation of parameters and analytical solution class
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);

	//Vector in which the analytical Solutions are stored
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
	auto start = std::chrono::high_resolution_clock::now();
	printer.print(parameters, duFortFrankel.schemeName(), duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	auto finish = std::chrono::high_resolution_clock::now();
	std::cout << "Dufort : " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
	
	computationalTimeResults.push_back(duFortFrankel.schemeName() + ";" + std::to_string(duFortFrankel.getComputationalTime()));

	//Richardson
	start = std::chrono::high_resolution_clock::now();
	printer.print(parameters, richardson.schemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	finish = std::chrono::high_resolution_clock::now();
	std::cout << "Richard : " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
	
	computationalTimeResults.push_back(richardson.schemeName() + ";" + std::to_string(richardson.getComputationalTime()));

	
	//Print the results of the Implicit Schemes and get the respective computationaltime
	//Laasonen in a for loop to compute for the different deltaT
	for (int unsigned indexDeltaT = 0; indexDeltaT < parameters.getVecDeltaT().size(); ++indexDeltaT)
	{
		start = std::chrono::high_resolution_clock::now();
		Laasonen laasonen = Laasonen(parameters, parameters.getVecDeltaT()[indexDeltaT]);
		printer.print(parameters, laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]), laasonen.solve(parameters, indexDeltaT));
		finish = std::chrono::high_resolution_clock::now();
		std::cout << "Laasonen" << parameters.getVecDeltaT()[indexDeltaT] << " : " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
		
		computationalTimeResults.push_back(laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]) + ";" + std::to_string(laasonen.getComputationalTime()));
	}
	//CrankNicolson only with the first deltaT (0.01)
	//It would be nice if 0 had a variable name (firstdeltaT or something like that)
	start = std::chrono::high_resolution_clock::now();
	CrankNicolson crankNicolson = CrankNicolson(parameters, parameters.getVecDeltaT()[0]);
	printer.print(parameters, crankNicolson.schemeName(), crankNicolson.solve(parameters, 0));
	finish = std::chrono::high_resolution_clock::now();
	std::cout << "Crank : " << std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() << "ns\n";
	
	computationalTimeResults.push_back(crankNicolson.schemeName() + ";" + std::to_string(crankNicolson.getComputationalTime()));

	//Printing the computational times of each scheme (laasonen has a different computational time for each deltaT) in a csv file
	printer.printComputationalTime(computationalTimeResults);

	return 0;
}