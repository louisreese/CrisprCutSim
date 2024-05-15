/*
 *
 *  Simulate digestion of DNA or RNA by CRISPR nucleases.
 *
 *  crisprcutsim.h
 *  
 *  Created by Louis Reese on 18.01.2021
 *  Copyright 2021 Louis Reese. All rights reserved.
 *
 *	
 */

#include <deque>
#include <gsl/gsl_rng.h>

class SIM
{
public:
	// Utility functions and variables
	gsl_rng * r; 	// GNU Scientific Library random numbers
	
	void InitClass(char *parameters[]);	// Initialize parameters
	void RngInit(char *parameters[]);	// Random number generator initialisation
	void printCONF(std::ostream& os);	// Print configuration
	std::string createFilename(const std::string &base); // Create filename with "_Size_k1_RanInit.dat"
	
	long int RanInit;
	int i;
	
	// Simulation algorithm
	int KIN(char *parameters[], void (SIM::*reaction)(int i), std::ostream& os);	
	
	// Functions to update configuration by splitting one polymer
	void makeSPLIT(int i);			// Discards unlabelled polymers
	void makeSPLITunlabelled(int i);	// Keeps unlabelled polymers

	// Important parameters in the simulation
	int Size, MAX_count, Number;
	double k1;
	
private:
	// Variables used during the simulation
	int count,  COUNTDATA;
	double dt, Time, Clock, Clock_count;
	double ran, mean, num;
	int ran_int, position;
	int newsize1, newsize2;
	
	std::deque <double> RATES;		// Propensity vector
	std::deque < unsigned long int > CONF; 	// Current polymer configuration 

};	
