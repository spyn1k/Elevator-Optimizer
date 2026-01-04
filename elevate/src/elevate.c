#include "elevate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	//Needs program name + inputfile at minimum
	if (argc < 2)
	{
		printf("Usage: %s <input_file> [--mode=recurse|brute|memoize|dp]\n" , argv[0]);
		return 1;
	}
	

	/*Open file*/
	char *filename = argv[1];
	FILE *file = fopen(filename , "r");


	if (file == NULL)
	{
		printf("Error: Could not open file %s", filename);
		return 1;
	}


	/*Read data*/
	
	int numPeople; //Total passengers
	int numStops;  //Max stops the elevator can make


	//Checks the count of successful reads
	if (fscanf(file, "%d %d", &numPeople , &numStops) != 2)
	{
		printf("Error: Invalid file format.\n");
		fclose(file); 
		return 1;
	}


	//When the program runs, it asks for memory according to the numPeople 
	int *dests = (int *)malloc(numPeople * sizeof(int));

	//if pc is out of ram malloc returns NULL
	if (dests == NULL)
	{
		printf("Error: Memory allocation failed.\n");
		fclose(file);
		return 1;
	}



	/*READ DESTINATIONS*/
	 
	for (int i=0; i < numPeople; i++)
	{
		//we expect 1 number/person
		if(fscanf(file,"%d", &dests[i]) != 1)
		{
			printf("Error: File ended too early.\n"); //fewer people than expected
			free(dests);
			fclose(file);
			return 1;		
		}
	}


	/*Since we have all the data in RAM we need*/

	fclose(file); //Closing file connection
	
	/*Default Mode*/ 
	char *mode = "dp";

	
	if (argc >= 3) //Checks if a 3rd argument was typed
	{
		if (strncmp,(argv[2] , "--mode=" , 7) == 0)
		{
			mode = argv[2] + 7; // Skip the first 7 characters ("--mode=") to point directly to the text that comes after it
		}
	}
		

	/*EXECUTE THE CHOSEN STRATEGY*/

	
	if (strcmp(mode, "recurse") ==0 )
	{
		solve_recurse(numPeople,numStops,dests);
	}
		else if (strcmp(mode, "brute") == 0)
		{
			solve_brute(numPeople,numStops,dests);
		}
		
		else if (strcmp(mode, "memoize") == 0)
		{
			solve_memoize(numPeople,numStops,dests);
		}
		else if (strcmp(mode, "dp") == 0)
		{
			solve_dp(numPeople,numStops,dests);
		}
			else //If mode is unknown, it turns into default (dp)
			{
				solve_dp(numPeople,numStops,dests);
			}
	
	//cleanup
	free(dests);

	return 0;
}

	int count_walking_cost(int lower_stop, int upper_stop, int *dests, int numPeople)
	{
		int total_cost = 0;

		for (int i=0; i < numPeople ; i++)
		{
			int d = dests[i];
			
				//count passengers whose dest is between the 2 stops
				if (d > lower_stop && d <= upper_stop)
				{
					//Calculate distance if they get off at the lower stop
					int walk_up = abs(d - lower_stop);
					
					int walk_down = abs (upper_stop - d); //calculate distance if they get off at the upper stop
				
					if (walk_up <= walk_down)
					{
						total_cost += walk_up;
					}
						else
						{
							total_cost += walk_down;
						}
				}
		}
		return total_cost;
	}
