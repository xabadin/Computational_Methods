#ifndef PRINTER_H // include guard
#define PRINTER_H
#include"parameters.h"
#include<string>
#include<fstream>

class Printer
{
private:
	// Vector of the Analytical Solutions 
	std::vector<std::vector<double>> analyticalSolutions;

public:
	// Default constructor
	Printer(); 

	// Alternate Constructor with parameters
	Printer(std::vector<std::vector<double>> analyticalSolutions);

	// Print the results of each scheme: DuFort-Frankel, Richardson, Laasonen and Crank-Nicholson
	void print(Parameters parameters, std::string filename, std::vector<std::vector<double>> schemesolutions);

	// Print the results of the Analytical solution
	void printAnalytical(Parameters parameters);

	// Print the results of the computational time
	void printComputationalTime(std::vector<std::string> computationalTimeResults);
};

#endif
