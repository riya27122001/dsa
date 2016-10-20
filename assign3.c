#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, i, w[20], W, count=0;

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
				printf("%d\n",w[i]);
				val=1;
			}
		
		else
			val=knapsack(W,i+1); //Trying new paths to sum up to W
		return val;
	}
	
	if (( argc != 2 )||(atoi(argv[1])>20)) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf("%d %d\n",argc, atoi(argv[1]));
        printf( "usage: %s no._of_array_elements(max. 20)\n", argv[0] );
        
    }

    else
    {
    	n = atoi(argv[1]);
   		printf("Enter array elements:\n");
	    for (i = 0; i < n; ++i)
	    {
	    	scanf("%d", &w[i]);
	    }
	    printf("Enter required weight:\n");
	    scanf("%d", &W);
	    if (knapsack(W,0)==0)
	    {
	    	printf("No such series found.\n"); //Knapsack returns 0(false)
	    }
	    else
	    {
	    	printf("No. of times knapsack was run: %d\n",count );
	    }
	}    
	return 0;
}