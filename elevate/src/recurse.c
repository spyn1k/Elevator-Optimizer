#include "elevate.h" 

//function to calculate formula
long long get_m(int i, int j, int numPeople, int *dests, int max_floor)
{
	//base case 
	if (i == 0)
	{
		return count_walking_cost(0, max_floor, dests, numPeople);
	}

	long long min_val = -1; //-1 -> havent found a cost yet

	for (int k = 0; k <= j; k++)
	{
		long long m_prev = get_m(i - 1, k, numPeople, dests, max_floor); //get cost for i-1 stops ending at k
	
		//walking adjustments
		int fw_k_inf = count_walking_cost(k, max_floor, dests, numPeople);
		int fw_k_j = count_walking_cost(k, j, dests, numPeople);
		int fw_j_inf = count_walking_cost(j, max_floor, dests, numPeople);

		//combine them
		long long current_val = m_prev - fw_k_inf + fw_k_j + fw_j_inf;

		//update min
		if(min_val == -1 || current_val < min_val) 
		{
			min_val = current_val;
		}
	}
	return min_val;
}

void solve_recurse(int numPeople, int numStops, int *dests) 
{
	int max_floor = 0;
	
	for (int i = 0; i < numPeople; i++)	//find max destination
	{
		if (dests[i] > max_floor)
		{
			max_floor = dests[i];
		}
	}



//check j floors to see which is best final stop 
long long global_min_cost = -1;
int best_last_stop = 0;

	for (int j = 0; j <= max_floor; j++)
	{
		long long cost = get_m(numStops, j, numPeople, dests, max_floor);

		//prefer lower floors on ties ~pdf
        	//we check floors 0 -> Max
		//strict '<' keeps the first (lowest) winner.
		if (global_min_cost == -1 || cost < global_min_cost)
		{
			global_min_cost = cost;
			best_last_stop = j;
		}
	}

	printf("Last stop at floor : %d\n", best_last_stop);
	printf("The minimum cost is : %lld\n", global_min_cost);
}
