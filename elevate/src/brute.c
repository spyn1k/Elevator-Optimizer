#include "elevate.h"

//global tracking for best solution
long long best_cost_brute = -1;
int *best_stops_brute = NULL;
int best_num_stops_brute = 0;


long long calculate_brute_cost(int *current_stops, int stop_count, int numPeople, int *dests)
{
	long long total = 0;
	int prev_stop = 0;	//start from ground
				
	for (int i = 0; i < stop_count; i++)
	{
		int current = current_stops[i];

		//add cost for ppl between prev and curr stop
		total += count_walking_cost(prev_stop, current, dests, numPeople);

		prev_stop = current;
	}

	total += count_walking_cost(prev_stop, 1000000000, dests, numPeople);
	return total;
}

//Recursive helper for combinations
void generate_combinations(int start_floor, int stops_left, int *current_stops, int pos,
			   int max_floor, int numPeople, int *dests)
{
	//base case
	if (stops_left == 0)
	{
		long long cost = calculate_brute_cost(current_stops, pos, numPeople, dests);

		//update global best if cheaper
		if (best_cost_brute == -1 || cost < best_cost_brute)
		{
			best_cost_brute = cost;
			best_num_stops_brute = pos;

			//save winning comb
			for (int k = 0; k < pos; k++)
			{
				best_stops_brute[k] = current_stops[k];
			}
		}
		return;
	}

	//try adding every valid floor as the next stop
	for (int f = start_floor; f <= max_floor; f++)
	{
		current_stops[pos] = f;
		//recurse for next stop (must be > f)
		generate_combinations(f + 1, stops_left - 1, current_stops, pos + 1,
					max_floor, numPeople, dests);
	}
}



void solve_brute(int numPeople, int numStops, int *dests)
{   
    //find max dest
    int max_floor = 0;

    for (int i = 0; i < numPeople; i++)
    {
	    if(dests[i] > max_floor)
	    {
	    	max_floor = dests[i];
	    }
    }
    //Initialize globals
    best_cost_brute = -1;
    best_stops_brute = malloc(numStops * sizeof(int));
    int *current_stops = malloc(numStops * sizeof(int));

    //try all combinations sizes 
    for (int s = 1; s <= numStops; s++)
    {
	    if (s > max_floor) break; //cant stop more times than floors exist
		
	    generate_combinations(1, s, current_stops, 0, max_floor, numPeople, dests);
    }

    //Print results
    if (best_cost_brute == -1)
    {
	    printf("No lift stops\n");
	    
	    //only walking cost (from the ground)
	    long long walk_cost = count_walking_cost(0, 1000000000, dests, numPeople);
	    printf("The minimum cost is : %lld\n", walk_cost);
    } 
    else
    {
	    printf("Lift stops are :");
	    for (int i = 0; i < best_num_stops_brute; i++)
	    {
		    printf(" %d", best_stops_brute[i]);
	    }
	    printf("\n");
	    printf("The minimum cost is : %lld\n", best_cost_brute);
    }

    /*---CLEANUP---*/

    free(best_stops_brute);
    free(current_stops);
}
