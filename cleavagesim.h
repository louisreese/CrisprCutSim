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
	
	long int RanInit;
	int i;
	
	int KIN(char *parameters[]);	// Stochastic simulation algorithm
	
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
	
	// Functions to update configuration by splitting one polymer
	void makeSPLIT(int i);				// Discards unlabelled polymers
	void makeSPLITunlabelled(int i);	// Keeps unlabelled polymers
	
};	
