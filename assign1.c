#include <stdio.h>
#include <string.h>


struct node
	{
		char name[30];
		int color;
			
	};
int greedy(int newclr1, int num1, struct node graph1[30], int inc1[30][30])
{
	int i1,j1,x1,found,count=0, colorTab1[30][30];
	/*
	colorTab1[][] stores the elements belonging to each colour row-wise.
	inc1[][] stores the static incidence matrix, denoting the connections between the nodes.
	*/
	printf("%d: ", newclr1);
	//Initialising colorTab1[][] to 0
	for (i1 = 1; i1 <= num1; ++i1)
	{
		for (j1 = 1; j1 <= num1; ++j1)
		{
			colorTab1[i1][j1]=0;
		}
	}
	//Assigning elements to current colour, specified by newclr1
	for (i1 = 1; i1 <= num1; ++i1)
	{
		
		if (graph1[i1].color==0)
		{
			found = 0; //Assuming node has no shared edges with elements of newclr1
			j1=1;
			//In this while loop, if and edge is found, the element is not assigned to the given color
			while(colorTab1[newclr1][j1]!=0)
				{
					
					x1=colorTab1[newclr1][j1];
					if (inc1[x1][i1]==1)
						found=1;
					++j1;
					
				}
			//If no edge, found assigned to given color
			if (found==0)
				{
					
					colorTab1[newclr1][j1]=i1;	//Adding to current row of colorTab1 
					count++;					//Stores no. of elements assigned to current color
					graph1[i1].color=newclr1;	//Changing color value in graph structure
					printf("%s ", graph1[i1].name);
				}
		}		
	}
	printf("\n");
	return count;


}

int main(int argc, char const *argv[])
{
	
	struct node graph[30];
	
	int inc[30][30], x, newclr, i, j, cnt, num;
	char c;

	if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else 
    {
        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );

        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
            num = (int)fgetc(file)-48;
            
            
            for (i = 1; i <= num; ++i)
               {
               	fscanf(file, "%s", graph[i].name);
               	
               	graph[i].color=0;
               } 

            for (i = 1; i <= num; ++i)
            {
            	
            	for (j = 1; j <= num; ++j)
            	{
            		          
            		fscanf(file, "%d", &inc[i][j]);
            		
            		
            		
            	}
            	
            }
            fclose( file );
            newclr=1;
        	cnt=0;
        	
        	while(cnt<num)
        		{	
        			
        			cnt+=greedy(newclr,num,graph,inc); //No. of elements already assigned a color
        			++newclr;	//Incrementing color to assign other elements
        		}
        }
        

    }
	return 0;
}