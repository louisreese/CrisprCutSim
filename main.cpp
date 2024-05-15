/*
 *
 *  Simulate digestion of DNA or RNA by CRISPR nucleases.
 *
 *  main.cpp
 *  
 *  Created by Louis Reese on 18.01.2021
 *  Copyright 2021 Louis Reese. All rights reserved.
 *
 *	
 */

#include <iostream>
#include <fstream>
#include <gsl/gsl_rng.h>

#include "crisprcutsim.h"

using namespace std;

int main(int argc, char *argv[])
{	
	if ( argc != 4)
	{
	// Usage instructions
		std::cout << "usage:  " << argv[0] << " [Int - polymer size]" << " [Float - digestion rate]" << " [Int - rng seed]" << "\n";
		std::cout << "output: " << "[time] " << "[[Integer configuration array]] " << "[average polymer size]" << "\n";
		return 1;	
	}
	else
	{
	// Run simulation labelled DNA.
		SIM Labelled;	
		Labelled.RngInit(argv);
		Labelled.InitClass(argv);
		std::string filename1 = Labelled.createFilename("LABEL");
		std::ofstream file1(filename1);
		Labelled.printCONF(file1);
		while(Labelled.KIN(argv, &SIM::makeSPLIT, file1) > 0){}; 
		file1.close();
		
	// Run simulation UNlabelled DNA.
		SIM Unlabelled;
		Unlabelled.RngInit(argv);
		Unlabelled.InitClass(argv);
		std::string filename2 = Unlabelled.createFilename("UNLABEL");
		std::ofstream file2(filename2);
		Unlabelled.printCONF(file2);
		while(Unlabelled.KIN(argv, &SIM::makeSPLITunlabelled, file2) > 0){};
		file2.close();

		return 1;
	}
}

