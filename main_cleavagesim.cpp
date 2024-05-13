/*
 *
 *  Simulate digestion of DNA by nucleases.
 *
 *  main_cleavagesim.cpp
 *  
 *  Created by Louis Reese on 18.01.2021
 *  Copyright 2021 Louis Reese. All rights reserved.
 *
 *	
 */

#include <iostream>
#include <fstream>
#include <gsl/gsl_rng.h>

#include "cleavagesim.h"

using namespace std;

int main(int argc, char *argv[])
{	
	if ( argc != 4)
	{
	// Usage instructions
		std::cout << "usage:  " << argv[0] << " [Int - polymer size]" << " [Float - digestion rate]" << " [Int - rng seed]" << "\n";
		std::cout << "output: " << "[time] " << "[[Integer configuration array]] " << "[average polymer size]" << "\n";

	// Determine algorithm used in last compilation 
		char ch;
		fstream fp;
		fp.open("codestate.txt", fstream::in);
		if(!fp)
		{
			std::cout << "\nNo current information about the algorithm employed. Please recompile.\n";
			return 0;
		}
		while (fp.eof()==0)
		{
			fp.get(ch);
			std::cout << ch;
		}
		fp.close();
		std::cout << "\n";
		return 1;	
	}
	else
	{
	// Initialize simulation class 
		SIM First;
		First.InitClass(argv);
		First.RngInit(argv);

	// Save initial configuration of SIM class
		ofstream file_obj; 
		char * OFile;
		OFile = new char[80];
		sprintf (OFile, "cleavagesim.conf");
		file_obj.open(OFile, ios::app);
		file_obj.write((char*)&First, sizeof(First)); 
		file_obj.close();
		delete OFile;

	// Run simulation.
		while(First.KIN(argv)>0){}; 
	
		return 1;
	}
}

