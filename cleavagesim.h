/*
 *
 *  Simulate digestion of DNA by nucleases.
 *
 *  cleavagesim.h
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
	
	gsl_rng * r;
	
	void InitClass(char *parameters[]);	// Initialize parameters
	void RngInit(char *parameters[]);	// Random number generator

	void printCONF(std::ostream& os);	// Print configuration
	std::string createFilename(const std::string &base); // Create filename fo initial parameters.
	
	long int RanInit;
	int i;
	
	// Simulation algorithm
	int KIN(char *parameters[], void (SIM::*reaction)(int i), std::ostream& os);	
	
	// Functions to update configuration by splitting one polymer
	void makeSPLIT(int i);				// Discards unlabelled polymers
	void makeSPLITunlabelled(int i);	// Keeps unlabelled polymers

	int Size, MAX_count, Number;
	double k1;
	
private:
	// Variables
	int count,  COUNTDATA;
	double dt, Time, Clock, Clock_count;
	double ran, mean, num;
	int ran_int, position;
	int newsize1, newsize2;
	
	std::deque <double> RATES; 				// Propensity vector
	std::deque < unsigned long int > CONF; 	// Current polymer configuration 

	
};	
