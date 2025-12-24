#ifndef ELEVATE_H
#define ELEVATE_H

//If elevate.h gets used the other file gets access to the libraries

#include <stdio.h>
#include <stdlib.h>

void solve_recurse(int numPeople, int numStops, int *dests);
void solve_brute(int numPeople, int numStops, int *dests);
void solve_memoize(int numPeople, int numStops, int *dests);
void solve_dp(int numPeople, int numStops, int *dests);

#endif
