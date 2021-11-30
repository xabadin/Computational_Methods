#include"Printer.h"

Printer::Printer() {}

Printer::Printer(std::vector<std::vector<double>> vectors) {
	(*this).analyticalSolutions = vectors;
};

void Printer::print(Parameters parameters, std::string filename, std::vector<std::vector<double>> schemesolutions) {
	std::ofstream ofs(filename + ".csv");
	ofs << "x;Scheme;Error;Analytical" << std::endl;

	for (int unsigned t = 0; t < schemesolutions.size(); t++) {
		ofs << "T= " << ((double)t + 1.0) * 0.1 << std::endl;
		for (int x = 0; x < parameters.getSpacePoints(); x++) {
			ofs << x * 0.05 << ";" << schemesolutions[t][x] << ";" << schemesolutions[t][x] - analyticalSolutions[t][x] << ";" << analyticalSolutions[t][x] << std::endl;
		}
	}
}

void Printer::printAnalytical(Parameters parameters) {
	std::ofstream ofs("AnalyticalSolution.csv");
	ofs << "x;";
	for (double i = 0; i < parameters.getSpacePoints()*parameters.getDeltaX(); i += parameters.getDeltaX()) {
		ofs << i << ";";
	}
	ofs << std::endl;
	for (int unsigned i = 0; i < analyticalSolutions.size(); i++) {
		ofs << parameters.getVecOutputTimePoints()[i] << ";";

		for (int unsigned x = 0; x < analyticalSolutions[i].size(); x++) {
			ofs << analyticalSolutions[i][x] << ";";
		}
		ofs << std::endl;
	}
}

void Printer::printComputationalTime(std::vector<std::string> computationalTimeResults) {
	std::ofstream ofs("ComputationalTime.csv");
	for (int unsigned i = 0; i < computationalTimeResults.size(); i++) {
		ofs << computationalTimeResults[i] << std::endl;
	}
}

