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

#include "cleavagesim.h"


using namespace std;

// Initialise GSL random number generator
void SIM::RngInit(char *parameters[]){
       r = gsl_rng_alloc(gsl_rng_mt19937);
       RanInit=(long int)atoi(parameters[3]);
       gsl_rng_set(r, RanInit);
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

	/* Display configuration on terminal:
		First row: time
		2nd to n-1 row: configuration
		nth row: average length of the configuration
	*/
		
	std::cout << "0 " ;
	for (int k=0; k<=CONF.size(); k++) {
			std::cout << CONF[k] << " ";
			position = position + (k)*CONF[k];
		}
	std::cout << " " << Size << "\n";

}

// Update the configuration labelled DNA
void SIM::makeSPLIT(int i){
	CONF[i]=CONF[i]-1;
	newsize1 = 1 + gsl_rng_uniform_int(r,i-1);
	CONF[newsize1] = CONF[newsize1] + 1;
}

// Update the configuration UNlabelled DNA
void SIM::makeSPLITunlabelled(int i){
	CONF[i]=CONF[i]-1;
	newsize1 = 1 + gsl_rng_uniform_int(r,i-1);
	CONF[newsize1] = CONF[newsize1] + 1;
	newsize2 = i - newsize1;
	CONF[newsize2] = CONF[newsize2] + 1;
}

// Perform the simulation
int SIM::KIN(char *parameters[]) 
{
	// Create reaction rate array
	RATES.clear();
	RATES.push_back(0.0);
	
	for(int k=1; k<=Size; k++){
		RATES.push_back(RATES.back() + k1 * CONF[k]*(k-1));
	}

	/* 
	The Gillespie Algorithm
	*/

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

	// Implement the reaction, alternative: change to makeSPLITunlabelled
	makeSPLIT(i); 

	// Display the configuration to terminal
	if (Time > Clock){
		
		std::cout << Time << " " ;
		position = 0;
		num = 0;
		for (int k=1; k<=CONF.size(); k++) {
				std::cout << CONF[k] << " ";
				position = position + (k)*CONF[k];
				mean = k*CONF[k];
				num = num + CONF[k];
			}
		// std::cout << position << " " ;
		std::cout << position/num << "\n";
		Clock = Clock + Clock_count;
	}
	
	if (CONF[1] ==  MAX_count) return 0;
	else return 1; 
}

