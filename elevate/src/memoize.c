/**
 * File: memoize.c
 * it offers memoized recursion
 * Adds a memo table to the recursive logic 
 * drastically speeds up performance by saving results we already calculated
 */

#include "elevate.h"
#include <stdlib.h>
	
//i = stops , j = floor
//global for easy access for function
long long **memo;

long long get_m_memo(int i, int j, int numPeople, int *dests, int max_floor)
{	
	//optimization
	if (memo[i][j] != -1)
	{
		return memo[i][j];
	}

	//base case , means everyone walks from the ground
	if (i == 0)
	{
		long long res = count_walking_cost(0, 1000000000, dests, numPeople);
		//cache it so we dont recalculate later
		memo[i][j] = res;
		return res;
	}

	long long min_val = -1;

	//Try every possible previous stop to find cheapest path
	for(int k = 0; k <= j; k++)
	{
		long long m_prev = get_m_memo(i - 1, k, numPeople, dests, max_floor);

		//calculate walking adjustments
		int fw_k_inf = count_walking_cost(k, 1000000000, dests, numPeople);
		int fw_k_j = count_walking_cost(k, j, dests, numPeople);
		int fw_j_inf = count_walking_cost(j, 1000000000, dests, numPeople);
		
		//take cost ending at 'k' , remove old penalty for people above 'k' and add new costs
		long long current_val = m_prev - fw_k_inf + fw_k_j + fw_j_inf;

		//Keep smallest cost found
		if(min_val == -1 || current_val < min_val)
		{
			min_val = current_val;
		}
	}

	//save the the answer
	memo[i][j] = min_val;
	return min_val;
}

void solve_memoize(int numPeople, int numStops, int *dests)
{   
	//find the highest floor
	int max_floor = 0;

	for(int i = 0; i < numPeople; i++)
	{
		if (dests[i] > max_floor) max_floor = dests[i];
	}

	//if we have more stops than floors cap it
	if (numStops > max_floor) 
	{
       		numStops = max_floor;
    	}

	//rows = stops, cols = floors
	memo = (long long**)malloc((numStops + 1) * sizeof(long long *));

	for (int i = 0; i <= numStops; i++)
	{
		memo[i] = (long long *)malloc((max_floor + 1) * sizeof(long long));

		//fill with -1 to mark them as unknown
		for (int j = 0; j <= max_floor; j++)
		{
			memo[i][j] = -1;
		}
	}

	//Find absolute minimum by checking very possible final floor
	long long global_min_cost = -1;
	int best_last_stop = 0;

	for (int j = 0; j <= max_floor; j++)
	{
		long long cost = get_m_memo(numStops, j, numPeople, dests, max_floor);

		//tiebreaker, if costs are the same the < keeps the lower floor
		if (global_min_cost == -1 || cost < global_min_cost)
		{
			global_min_cost = cost;
			best_last_stop = j;
		}
	}

	if (best_last_stop == 0) 
	{
    	printf("No lift stops\n");
	} 
		else 
		{
		    printf("Last stop at floor: %d\n", best_last_stop);
		}
	
	printf("The minimum cost is: %lld\n", global_min_cost);
	
	for (int i = 0; i <= numStops; i++)
	{
		free(memo[i]);
	}
	free(memo);
}

