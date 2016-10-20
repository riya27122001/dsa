#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

int n, i, w[20], W, count=0, min=INT_MAX, j, k, x;
long int max =0;

int main(int argc, char const *argv[])
{
	int knapsack(int W, int i)
	{
		int val; //Return value
		++count; //Incrementing count to find no. of times knapsack was run
		if(W==0) //Done finding all numbers which sum up to initial W, hence W reduced to 0
			val=1;
		else if((W<0)||(i>=n)) //Series not found by following prev path
			{
				val=0;
			}
		else if(knapsack(W-w[i],i+1)) //Proceeding along path to sum up to W
			{
				// printf("%d\n",w[i]);
				val=1;
			}
		
		else
			val=knapsack(W,i+1); //Trying new paths to sum up to W
		return val;
	}
	printf("n\t Max\t\t Min\n");
	for (i = 1; i <= 20; ++i)
	{
	
	    n=i;
	    for (j = 0; j < 10000; ++j)
	    {
	    
		    for (k = 0; k < n; ++k)
		    {
		    	srand(time(NULL));
				w[k] = rand()%(n+1);
		    }
		    srand(time(NULL));
			W = rand()%(n*n/2+1);
			x=knapsack(W,0);
		    if (count>max)
		    {
		    	max=count;
		    }
		    if (count<min)
		    {
		    	min=count;
		    }
		    
		    count=0;
		}
		printf("%d\t %ld\t\t %d\n",n,max,min);
	}    
	return 0;
}
//Table generated for Max and Min values for each n
// n	 Max		 Min
// 1	 1		 	 1
// 2	 1		 	 1
// 3	 7		 	 1
// 4	 20		 	 1
// 5	 63		 	 1
// 6	 63		 	 1 
// 7	 255		 1
// 8	 255		 1
// 9	 511		 1
// 10	 511		 1
// 11	 511		 1
// 12	 8191		 1
// 13	 8191		 1
// 14	 8191		 1
// 15	 65219		 1
// 16	 108993		 1
// 17	 262143		 1
// 18	 524287		 1
// 19	 1048575	 1
// 20	 2097151	 1

/*
Max. no. of times Knapsack has to run will be of the order 2^n as the worst case
occurs when Knapsack has to try all possible summation combinations, which is equal to
2^n


*/