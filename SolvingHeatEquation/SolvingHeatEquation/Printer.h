#ifndef PRINTER_H
#define PRINTER_H
#include"parameters.h"
#include<iostream>
#include<vector>
#include<string>

class Printer
{
private:
	std::vector<std::vector<double>> analyticalSolutions;
public:
	Printer(); //default constructor
	Printer(Parameters parameters, std::vector<std::vector<double>> analyticalSolutions); //Constructor with parameters

	void print(Parameters parameters, std::string filename, std::vector<std::vector<double>> schemesolutions);
	void printAnalytical(Parameters parameters);
	void printComputationalTime(std::vector<std::string> computationalTimeResults);
};
#endif