#pragma once
#ifndef DUFORTFRANKEL_H
#define DUFORTFRANKEL_H

#include"ExplicitSchemes.h"
#include<string>

class DuFortFrankel : public ExplicitSchemes {
public:

	DuFortFrankel(); //Default constructor
	DuFortFrankel(Parameters parameters); //Constructor with parameters

	double NextTimeStep(Parameters parameters, int i, double DeltaT); //Compute result using v0 <=> (n-1) and v1 <=> (n) values to find v2 <=> (n+1) values
	double getTimeStep1(Parameters parameters, int i, double DeltaT);
	std::string schemeName(); //Return name of the scheme, used in the printer class

};
#endif
