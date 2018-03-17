#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char** argv) //arguments to main(), to accept the value of n from command line
{
	clock_t start, end; //variables that count the start time and end time of our calculations
	//time_t t;	
	int run = 1;
	
		srand(time(NULL)); //to randomize the random number generation
		int n;
		n = atoi(argv[1]);
		int query;
		int arr[n];

		int i;
		for(i = 0; i < n; i++)
		{
			//srand(time(NULL));		
			arr[i] = rand(); //generating a random integer
		}

	start = clock(); //we note down the start time here
	while(run <= 10000) //we run a loop for analysing 10000 inputs
	{	
		int toss;
		//srand(time(NULL));
		toss = rand()%2; //to simulate a toss, we have generated a random number that can take only two values, 0 or 1
		if(toss == 0) //if heads 
		{	
			query = rand(); //we generate any random number as query element
		}
		else //if tails 
		{
			int k;
			k = rand()%n; //we generate a random number in the range of array indices
			query = arr[k]; //query element is assigned to be the number at that index to ensure that it will be found in the array
		}

		int found = 0; //a flag variable to keep track of whether or not the query element is found
		
		for(i = 0; i < n; i++) //a simple for-loop to carry out the search
		{
			if(query == arr[i])
			{
				found = 1;
				break;
			}
		}
				
		run++;
	}
	end = clock(); //we note down the end time of our calculations
	double time_taken = (double)(end - start)/CLOCKS_PER_SEC; //finding the total time taken for 10000 runs
	printf("Time taken = %.10lf\n", time_taken/10000.0); //displaying the average time taken per run
	return 0;
}
		
