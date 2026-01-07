/**
 * File: dp.c
 * it is a dynamic programming solver (Bottom-Up)
 * Fills the cost table repeatedly from 0 stops up to N stops
 */

#include "elevate.h"
#include <stdlib.h>

void solve_dp(int numPeople, int numStops, int *dests,int debug)
{   
	//find max floor
	int max_floor = 0;

	for (int i = 0; i < numPeople; i++)
	{
		if (dests[i] > max_floor) max_floor = dests[i];
	}

	//if we have more stops than floors cap it
        if (numStops > max_floor)
        {
                numStops = max_floor;
        }

	//alloc dp table
	//i = rows (number of stops), j = cols(floor loc of the ith stop)
	long long **dp = (long long**)malloc((numStops + 1) * sizeof(long long*));
	int **parent = (int**)malloc((numStops + 1) * sizeof(int*)); //table to reconstruct path

	for (int i = 0; i <= numStops; i++)
	{
		dp[i] = (long long *)malloc((max_floor + 1)* sizeof(long long));
		parent[i] =(int *)malloc((max_floor + 1)* sizeof(int));
	}

	//base case 0 stops
	//cost stays the same regardless of j
	long long base_cost = count_walking_cost(0, 1000000000, dests, numPeople);

	for (int j = 0; j <= max_floor; j++)
	{
		dp[0][j] = base_cost;
		parent[0][j] = 0; //Predecessor of base case is ground
	}

	//fill table
	for (int i =1; i<= numStops; i++)
	{	
		for (int j =0; j <= max_floor; j++) //trying every possible flor
		{
			long long min_val = -1;
			int best_k = 0; //to store best previous stop

			for (int k = 0; k <= j; k++) 	//best 'k' to minimize cost
			{
				long long m_prev = dp[i-1][k];	//look at previous stop at 'k'
			
				int fw_k_inf = count_walking_cost(k, 1000000000, dests, numPeople);
				int fw_k_j = count_walking_cost(k, j, dests, numPeople);
				int fw_j_inf = count_walking_cost(j, 1000000000, dests, numPeople);

				long long current_val = m_prev - fw_k_inf + fw_k_j + fw_j_inf;

				//update best k
				if (min_val == -1 || current_val < min_val)
				{
					min_val = current_val;
					best_k = k;
				}
			}
			//save best cost for this cell
			dp[i][j] = min_val;
			parent[i][j] = best_k; //remember where we came from
		}
	}
	

	/*--DEBUG PRINTING--*/
	if (debug)
	{	
		for (int i = 0;i <= numStops; i++)//loop through every number of stops
		{										//this loop prints the dp table
			for(int j = 0; j <= max_floor; j++)//loop through every number of floors
			{
				if (j < max_floor) //if we are not at the end of the line
				{
					printf("%2lld ", dp[i][j]);
				}
				else //if we are at the end of the line
				{
					printf("%2lld", dp[i][j]);
				}
			}//move to next line
			printf("\n");
		}
	}


	//find global min
	//look at last row and find best floor col
	long long global_min_cost = -1;
	int best_last_stop = 0;

	for (int j = 0; j <= max_floor; j++)
	{
		long long cost = dp[numStops][j];

		if (global_min_cost == -1 || cost < global_min_cost)
		{
			global_min_cost = cost;
			best_last_stop = j;
		}
	}

	if (best_last_stop == 0)
	{
		printf("No lift stops\n");
		printf("The minimum cost is: %lld\n", global_min_cost);
	}
	else
	{

		//Reconstruct path using parent table
		//store them in array cause we backtrack
		int *final_stops = malloc((numStops + 1) * sizeof(int));
		int count = 0;

		int curr_floor = best_last_stop;
		int curr_stop_idx = numStops;
	
		//Backtrack
		while(curr_stop_idx > 0 && curr_floor > 0)
		{
			final_stops[count++] = curr_floor;
			curr_floor = parent[curr_stop_idx][curr_floor];
			curr_stop_idx--;
		}

		printf("Lift stops are:");

		//print in correct order (reverse backtrack)
		for (int k = count - 1; k >= 0; k--)
		{
			printf(" %d", final_stops[k]);
		}

		printf("\n");
		printf("The minimum cost is: %lld\n", global_min_cost);

		free(final_stops);
	}

	for (int i = 0; i <= numStops; i++)
	{
		free(dp[i]);
		free(parent[i]);
	}
	free(dp);
	free(parent);
}
