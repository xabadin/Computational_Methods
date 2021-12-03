#ifndef RICHARDSON_H
#define RICHARDSON_H

#include"ExplicitSchemes.h"
#include<string>

class Richardson : public ExplicitSchemes {
public:

	Richardson(); //Default constructor
	Richardson(Parameters parameters); //Constructor with parameters

	double NextTimeStep(Parameters parameters, int i, double DeltaT); //Compute result using v0 <=> (n-1) and v1 <=> (n) values to find v2 <=> (n+1) values
	double getTimeStep1(Parameters parameters, int i, double DeltaT);
	std::string schemeName(); //Return name of the scheme, used in the printer class
};


#endif

