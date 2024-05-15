/*
 *
 *  Simulate digestion of DNA by nucleases.
 *
 *  cleavagesim.cpp
 *  
 *  Created by Louis Reese on 18.01.2021
 *  Copyright 2021 Louis Reese. All rights reserved.
 *
 *	
 */

#include <iostream>
#include <math.h>
#include <sstream>
#include <iomanip>  // For std::setprecision

#include "crisprcutsim.h"

using namespace std;

// Initialise GSL random number generator
void SIM::RngInit(char *parameters[]){
       r = gsl_rng_alloc(gsl_rng_mt19937);
       RanInit=(long int)atoi(parameters[3]);
       gsl_rng_set(r, RanInit);
}

// Creat Filename including parameter values
std::string SIM::createFilename(const std::string &base) {
    std::ostringstream oss;
    oss << base << "_" << std::fixed << std::setprecision(8) << SIM::Size << "_" << SIM::k1 << "_" << SIM::RanInit << ".csv";
    return oss.str();
}

//Initiallise constants and simulation parmeters
void SIM::InitClass(char *parameters[]){
	Size=atoi(parameters[1]);	// Size of the polymers to be cleaved
	k1=atof(parameters[2]);	// Cleavage rate 
	MAX_count=1000000;		// Number of polymers at the start of the simulation
	CONF.clear();			
	CONF.resize(Size,0); 	// Configuration of the simulation
	CONF[Size]=MAX_count;	// Initialise with MAX_count polymers of length Size

	Time=0.0;	// Initialize simulation time
	
	Clock_count = 1.0;
	Clock = 1;
	// printCONF(fs);
}

// Update the configuration labelled DNA keep only the labelled DNA molecule
void SIM::makeSPLIT(int i){
	CONF[i]=CONF[i]-1;
	newsize1 = 1 + gsl_rng_uniform_int(r,i-1);
	CONF[newsize1] = CONF[newsize1] + 1;
}

// Update the configuration UNlabelled DNA, splits DNA in two
void SIM::makeSPLITunlabelled(int i){
	CONF[i]=CONF[i]-1;
	newsize1 = 1 + gsl_rng_uniform_int(r,i-1);
	CONF[newsize1] = CONF[newsize1] + 1;
	newsize2 = i - newsize1;
	CONF[newsize2] = CONF[newsize2] + 1;
}

// Perform the simulation
int SIM::KIN(char *parameters[], void (SIM::*reaction)(int i), std::ostream& os) {
	// Create propensities
	RATES.clear();
	RATES.push_back(0.0);
	
	for(int k=1; k<=Size; k++){
		RATES.push_back(RATES.back() + k1 * CONF[k]*(k-1));
	}

	// Determine exponentially distributed timestep
	dt=log(1/gsl_rng_uniform_pos(r))/(RATES.back());
	Time += dt;

	// Choose which of the reactions should be carried out
	// Important to note: 
	// the order has to be maintained corresponding to 
	// propensities in RATES[] container
	i=2;
	ran = gsl_rng_uniform_pos(r)*RATES.back();
	while (RATES.at(i)<ran) {i++;}

	// Implement the reaction based on which reaction scheme is used
	(this->*reaction)(i); 

	// Conditional output configuration to file
	if (Time > Clock){
		printCONF(os);
		Clock = Clock + Clock_count;
	}
	
	// Stop conditions for the program
	if ((CONF[1] >=  MAX_count && Time > 3600) || CONF[1] == MAX_count*Size) return 0;
	else return 1; 
}

//Utility function to print to any output stream
void SIM::printCONF(std::ostream& os) 
{
	/* Print configuration to file:
		First row: time
		2nd to n-1 row: configuration
		nth row: average length of the configuration
	*/
	
	os << Time << ", " ;
	position = 0;
	num = 0;
	for (int k=1; k<=CONF.size(); k++) {
		os << CONF[k] << ", ";
		position = position + k*CONF[k];
		num = num + CONF[k];
	}
	os << position/num << "\n";
}
