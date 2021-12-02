/***
*	Xabadin Bilbao, Kahina Chelli, Lucas Pin-Belloc
*	
*	MSc. Computational and Software Techniques in Engineering
*		Software Engineering for Technical Computing option
* 
*	School of Aerospace, Transport and Manufacturing
*				Cranfield University
*					2021 - 2022
*
*	1D HEAT CONDUCTION PARTIAL DIFFERENCIAL EQUATION SOLVER 
*/

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
	/*
	* Initialisation of parameters and analytical solution
	*/
	Parameters parameters = Parameters();
	AnalyticalSolution analyticalSolution = AnalyticalSolution(parameters);

	/*
	* Vector in which the analytical Solutions are stored
	*/
	std::vector<std::vector<double>> analyticalSolutions;

	/*
	* Vector to store the computational times of the different schemes
	*/
	std::vector<std::string> computationalTimeResults;

	/*
	* Generate the analytical solution for the different time points
	*/
	analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, 0.0));
	for (int unsigned i = 0; i < parameters.getVecOutputTimePoints().size(); i++) {
		analyticalSolutions.push_back(analyticalSolution.ComputeAnalyticalSolution(parameters, parameters.getVecOutputTimePoints()[i]));
	}

	/*
	* Initialisation of the explicit schemes
	*/
	DuFortFrankel duFortFrankel = DuFortFrankel(parameters);
	Richardson richardson = Richardson(parameters);

	// PRINT THE ANALYTICAL AND NUMERICAL SOLUTIONS AND COMPUTATIONAL TIME
	/*
	* Initialisatoin of the printer
	*/
	Printer printer = Printer(analyticalSolutions);
	
	/*
	* Print the analytical solution
	*/
	printer.printAnalytical(parameters);

	// Print explicit schemes solutions- DUFORT-FRANKEL AND RICHARDSON
	/*
	* Print DuFort-Frankel scheme results and get the computational time in the vector
	*/
	printer.print(parameters, duFortFrankel.schemeName(), duFortFrankel.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(duFortFrankel.schemeName() + ";" + std::to_string(duFortFrankel.getComputationalTime()));

	/*
	* Print Richardson scheme results and get the computational time in the vector
	*/
	printer.print(parameters, richardson.schemeName(), richardson.solve(parameters, parameters.getVecDeltaT()[0], parameters.getVecTimePoints()[0]));
	computationalTimeResults.push_back(richardson.schemeName() + ";" + std::to_string(richardson.getComputationalTime()));
	
	// Print implicit schemes solutions - LAASONEN AND CRANK-NICHOLSON
	/*
	* Print Laasonen scheme results and get the computational time in the vector
	* The results computed for the different DeltaT given of the heat problem definition
	*/
	for (int unsigned indexDeltaT = 0; indexDeltaT < parameters.getVecDeltaT().size(); ++indexDeltaT)
	{
		Laasonen laasonen = Laasonen(parameters, parameters.getVecDeltaT()[indexDeltaT]);
		printer.print(parameters, laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]), laasonen.solve(parameters, indexDeltaT));
		computationalTimeResults.push_back(laasonen.schemeName() + std::to_string(parameters.getVecDeltaT()[indexDeltaT]) + ";" + std::to_string(laasonen.getComputationalTime()));
	}

	/*
	* Print Crank-Nicholson scheme results and get the computational time in the vector
	*/	
	CrankNicolson crankNicolson = CrankNicolson(parameters, parameters.getVecDeltaT()[0]);
	printer.print(parameters, crankNicolson.schemeName(), crankNicolson.solve(parameters, 0));
	computationalTimeResults.push_back(crankNicolson.schemeName() + ";" + std::to_string(crankNicolson.getComputationalTime()));

	// Print computational time for each scheme - EXPLICIT AND IMPLICIT
	/*
	* The computational time of DuFort-Frankel, Richardson and Crank-Nicholson schemes computaional time for DeltaT = 0.01
	* Laasonen scheme has a different computational time for each deltaT
	*/
	printer.printComputationalTime(computationalTimeResults);

	return 0;
}
