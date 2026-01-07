#ifndef ELEVATE_H
#define ELEVATE_H

//If elevate.h gets used the other file gets access to the libraries

#include <stdio.h>
#include <stdlib.h>

//helper function to calculate walking cost, it is defined in elevate.c 
long long count_walking_cost(int lower_stop, int upper_stop, int *dests, int numPeople);

//solvers for the 4 different modes
//each in their own files
void solve_recurse(int numPeople, int numStops, int *dests);
void solve_brute(int numPeople, int numStops, int *dests);
void solve_memoize(int numPeople, int numStops, int *dests);
void solve_dp(int numPeople, int numStops, int *dests, int debug);

#endif
