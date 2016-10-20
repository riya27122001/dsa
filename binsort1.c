#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

//FInd no. of operations

// Reception data rate = lamda*Lavj
// Lavj = 815 = ((1550*1551)/2 - (79*80)/2)/(1550-79)

//Packet structure
struct packet{

int id; // packet id
time_t t0; // arrival time of packet
int L; // size of packet
char *contents; // pointer to contents of packet
struct packet *left; //binary tree pointers
struct packet *right;
};

typedef struct packet *Packet;
Packet tree; //Binary tree in which packets are sorted 
int l1=1, d1=0; 
//l1->Current length of binary tree
//d1->Total no. of packets dropped


//Function to determine time interval between arrival of packets ---- Poisson distribution

float nextTime(float rateParameter)
{
     float x, y;
     long int a,b;
     a=RAND_MAX;
     b=RAND_MAX+1;
     x=(float)(rand()%(a));
     y=(float)a;
     return (-logf(1.0f - (x/y))/rateParameter);
}

//Function to create tree with one node
Packet maketree(int id, int num, char *contents)
{
	Packet p;
	p = (Packet) malloc(sizeof(struct packet)); //Allocating memory to tree
	p->id=id;
	p->t0 = time(NULL);
	p->L=num; //num is the length of the added packet passed as a parameter
	p->contents = (char*) malloc(num*sizeof(char));
	strcpy(p->contents, contents);
	p->left=NULL; //since only one node, left and right point to NULL
	p->right=NULL;
	return p;
}

//to set left node of a node
void setleft(Packet p, int id, int num, char *contents)
{
	if(p==NULL)
		printf("Void Insertion\n");
	else if(p->left != NULL)
		printf("Invalid Insertion\n");
	else
		p->left = maketree(id,num,contents);
}

//to set right node of a node
void setright(Packet p, int id, int num, char *contents)
{
	if(p==NULL)
		printf("Void Insertion\n");  
	else if(p->right != NULL)
		printf("Invalid Insertion\n");
	else
		p->right = maketree(id,num, contents);
}


		
	

// To insert new node into tree
void binsert(int id, int num, char *contents, int N)
{
	
	
	Packet p,q;
	//Checking for Maximum no. of packets that can be queued
	if (l1==N)
		{
			printf("Dropping packet as max. queue size %d exceeded\n",N );
			++d1;
			
		}
	else
	{
		p=q=tree; //To ins every num have to traverse from top of tree
		
		while((num!=p->L)&&(q!=NULL))
		{
			
			p=q;
			if(num<p->L)
				q=p->left;
			else
				q=p->right;
		}

		//Checking for packets with same size, since assumption of question is that packets of uniform size arrive, duplicate packet
		//sizes cannot occur
		if (num==p->L)
			printf("%d is duplicate\n",num );

		//p points to the node to which new node is to be attached
		//If num less than length of p	 
		else if (num<p->L)
			{
				setleft(p,id,num,contents);
				++l1;
			}	
		//If num greater than length of p	 	
		else if (num>p->L)
			{
				setright(p,id,num,contents);
				++l1;
			}	

	}
		
		
	

}



//Function to dequeue smallest packet from queue
Packet binsmall(int N)
{
	Packet p,q,r;
	p=q=tree;
	//If tree is empty
	if (tree==NULL)
	{
		printf("Queue empty. Nothing dequeued.\n");
		p=NULL;
		++l1; //since l1(queue length) is decremented at the end of this fn. and in this case needn't be decremented
	}
	//If only one node present
	if ((tree->left==NULL)&&(tree->right==NULL))
		{
			
			tree=NULL;
			
		}	
	
		while(q!=NULL)
		{
			r=p;
			p=q;
			q=p->left;
		}
		// r finally holds the father of the node that is to be dequeued.
		// p is the node to be dequeued
		--l1; //Decrementing queue length
		
		r->left=p->right; //If p is dequeued, p->right is the next smallest node and should be r->left
		
		
	
	
	return p;

}

/*void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}*/

//Main Function
int main(int argc, char const *argv[])
{
	srand(time(NULL)); //To enable random number generation
	//Variables
	//N1->max queue length
	//num->length of current packet(to be enqueued)
	//mu->output data rate
	//lambda->input packet rate
	//en_flg, de_flg to check if packet has to be enqueued or dequeued
	//en_time_diff -> time left for packet to be enqueued
	//de_time_diff -> time left for packet to be dequeued
	//id1 -> Id of current packet
	//contents1 -> contents of current packet
	int N1, num1, mu, en_flg=1, de_flg=1, id1;
	float lambda;
	double en_time_diff, de_time_diff; 
	char *contents1;


	//Checking if CLI entered in correct format
	if ( argc != 5 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s [Max No. of array elements] [Input packet rate] [Output data rate] [Time for simulation in seconds] \n", argv[0] );
    }
    
    else 
    {
		
		printf("Keep enetering packets and hit Ctrl+C to exit program\n");
		//Initialising values of variables with CLI
    	N1 = atoi(argv[1]);
    	lambda = atoi(argv[2]);
    	mu = atoi(argv[3]);
    	
   		double t;
   		Packet p1;
    	
	    time_t endwait;
    	time_t enq_t = time(NULL);
    	time_t deq_t = time(NULL);
    	time_t curr_t = time(NULL);
  		time_t seconds = atoi(argv[4]); // after given seconds in CLI, end loop.
  		//Scanning first packet from user input
  		printf("Enter packet.\n");
  		printf("ID:\n");
    	scanf("%d",&id1);
  		printf("Length:\n");
    	scanf("%d",&num1);
    	contents1 = (char*) malloc(num1*sizeof(char));
    	printf("Contents:\n");
    	scanf("%s",contents1);
    	//Calculating next time for new packet
    	t=(double)(nextTime(lambda));
    	
    	en_time_diff = floorf(((double)((num1)/(815*lambda)))); //Time for packet to be received
        de_time_diff = en_time_diff; //First packet will be dequeued the same time as it is enqueued

    	endwait = curr_t + seconds; //End of network simulation

    	printf("start time is : %s", ctime(&enq_t));

    	//Simulating for time steps of one second.
    	while (curr_t < endwait)
    	{
        	/* Do stuff while waiting */
        	
        	//Invalid case of enqueuing time greater than dequeuing time
        	if (en_time_diff>de_time_diff)
        	{
        		printf("enqueue time diff should be : %f\n", en_time_diff);
        		printf("dequeue time diff should be : %f\n", de_time_diff);
        		printf("Enqueue time difference is greater than dequeue time difference. Program suspended.\n");
        		break;
        	}
        	//Time for receiving packet completed
        	if ((floorf(difftime(curr_t, enq_t))>=en_time_diff)&&(en_flg))
    		{
    			printf("Packet id: %d enqueued.\n",id1);
    			en_flg = 0;
    			if(tree==NULL)
				{
					tree=maketree(id1,num1,contents1);
					++l1;
				}
				else
					binsert(id1,num1,contents1,N1);
    		}
    		//Time for transmitting packet completed
    		if ((floorf(difftime(curr_t, deq_t))>=de_time_diff)&&(de_flg))
    		{
    			deq_t = time(NULL);
    			de_flg = 0;
    			p1=binsmall(N1);
    			if (p1!=NULL)
    			{
    				printf("Packet dequeued is %d.\n No. of dropped packets: %d\n Queue length:%d\n" ,p1->L,d1,l1 );
    			}
					
				
    		}
    		//nextTime for receiving new packet
    		//if (floorf(difftime(curr_t, enq_t))==floorf(t))
    		if (floorf(difftime(curr_t, enq_t))==floorf(15.000))
    		{
    			printf("Enter packet.\n");
    			en_flg=1;
    			de_flg=1;
    			printf("ID:\n");
    			scanf("%d",&id1);
  				printf("Length:\n");
    			scanf("%d",&num1);
    			contents1 = (char*) malloc(num1*sizeof(char));
    			printf("Contents:\n");
    			scanf("%s",contents1);
    			
    			enq_t = time(NULL);
    			t=(double)(nextTime(lambda));
    		}
        	sleep(1);   // sleep 1s. -> one second time step
        	curr_t = time(NULL);
        	en_time_diff = floorf(((double)((num1)/(815*lambda))));
        	de_time_diff = floorf((double)((p1->L)/mu));

        	

        	printf("loop time is : %s\n", ctime(&curr_t));
        	printf("Enqueue time is : %s\n", ctime(&enq_t));
        	printf("Dequeue time is : %s\n", ctime(&deq_t));
        	printf("Enqueue time diff is : %f\n", floorf(difftime(curr_t, enq_t)));
        	printf("Dequeue time diff is : %f\n", floorf(difftime(curr_t, deq_t)));
        	printf("enqueue time diff should be : %f\n", en_time_diff);
        	printf("dequeue time diff should be : %f\n", de_time_diff);
        	printf("time for next packet should be : %f\n", floorf(t));
    	}

    	printf("end time is %s", ctime(&endwait));

	   

	}	
	return 0;
}
