#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct packet
{
	char type[5];
	char *contents;	
	int delay;
} packet;

struct queue
{
	packet items[7000];
	int front, rear;
} q;

void equate(packet *p, packet *q)
{
	p->delay = q->delay;
	strcpy(p->type,q->type);
	if(!strcmp(p->type,"HTTP"))
	{
		p->contents = (char*) malloc(80*sizeof(char));
		strcpy(p->type,q->type);
	}
	else if(!strcmp(p->type,"Video"))
	{
		p->contents = (char*) malloc(400*sizeof(char));
		strcpy(p->type,q->type);
	}
}


int empty()
{
	
	return ((q.front == q.rear)? 1: 0);
}

int rem()
{
	int und = 0;
	if(empty())
	{
		printf("Queue Underflow\n");
		und =1;
	}
	else
	{
		free(q.items[q.front].contents);
		if(q.front==6999)
			q.front=0;
		else
			q.front++;
	}
	return und;
	
	
	
	
}

void insert(packet *x)
{
	int curr = q.rear;
	if (q.rear == 6999)
		q.rear=0;
	else
		q.rear++;
	if (q.rear==q.front)
	{
		printf("Queue overflow\n");
		q.rear = curr;
		//break;
	}
	strcpy(q.items[q.rear].type,x->type);
	q.items[q.rear].delay = 0;
	if(!strcmp(q.items[q.rear].type,"Video"))
	{
		q.items[q.rear].contents = (char*) malloc(400*sizeof(char));
		strcpy(q.items[q.rear].contents,x->contents);
	}
	else if(!strcmp(q.items[q.rear].type,"HTTP"))
	{
		q.items[q.rear].contents = (char*) malloc(80*sizeof(char));
		strcpy(q.items[q.rear].contents,x->contents);
	}
	

}

int drop(int i)
{
	

	int und = 0;
	if(i==(q.front+1))
		und=rem();
	else if(i==q.rear)
	{
		free(q.items[q.rear].contents);
		q.rear--;
	}
	return und;
	
}

int main()
{
	q.front = 6999;
	q.rear =6999;
	int bytes_in_queue, bytes_dequeued, bytes_enqueued, num_packet_drop, i, und1;
	float drop_percentage;
	printf("Keep enetering packets and hit Ctrl+C to exit program\n");
	time_t start_t = time(NULL);
	time_t seconds = 15;
	bytes_in_queue = 512000;
	num_packet_drop = 0;
	time_t endwait = start_t + seconds;
	packet p;
	printf("start time is : %s", ctime(&start_t));
	while (start_t < endwait)
	{
		//Dequeue
		printf("Dequeuing....\n");
		bytes_dequeued = 0;
		while((bytes_dequeued<64000)&&(bytes_in_queue>0))
		{
			

			if(!strcmp(q.items[q.front+1].type,"HTTP"))
			{
				printf("HTTP packet: %s\n dequeued.\n",q.items[q.front+1].contents );
				bytes_dequeued += 80;
				bytes_in_queue -= 80;
				free(q.items[q.front+1].contents);
			}
			else if(!strcmp(q.items[q.front+1].type,"Video"))
			{
				printf("Video packet: %s\n dequeued.\n",q.items[q.front+1].contents );
				bytes_dequeued += 400;
				bytes_in_queue -= 400;
				free(q.items[q.front+1].contents);
			}
			und1=rem();
			if(und1)
				break;
			
		}
		//Drop
		printf("Dropping....\n");
		while(q.items[q.rear].delay>=1)
		{
			if((q.items[q.rear].delay>=1)&&(!strcmp(q.items[q.rear].type,"Video")))	
			{
				
				++num_packet_drop;
				printf("Video packet: %s\n dropped.\n",q.items[q.rear].contents );
				und1=drop(q.rear);
				if(und1)
					break;
				free(q.items[q.rear].contents);
			}	
			else if((q.items[q.rear].delay>=15)&&(!strcmp(q.items[q.rear].type,"HTTP")))	
			{
				
				++num_packet_drop;
				printf("HTTP packet: %s\n dropped.\n",q.items[q.rear].contents );
				drop(q.rear);
				if(und1)
					break;
				free(q.items[q.rear].contents);
			}
			else
				break;
		}

		//Enqueue
		printf("Enqueuing....\n");
		bytes_enqueued=0;
		while(bytes_enqueued<32000)
		{
			printf("Enter packet.\n");
			printf("Type: HTTP or Video?\n");
			scanf("%s", p.type);
			printf("Contents:\n");
			if(!strcmp(p.type,"HTTP"))
			{
				p.contents = (char*) malloc(80*sizeof(char));
				bytes_enqueued += 80;
				bytes_in_queue += 80;
			}
			else if(!strcmp(p.type,"Video"))
			{
				p.contents = (char*) malloc(400*sizeof(char));
				bytes_enqueued += 400;
				bytes_in_queue += 400;
			}
			scanf("%s", p.contents);
			insert(&p);
			free(p.contents);
		}

		drop_percentage = 100*((float)num_packet_drop/(float)(q.rear-q.front));
		printf("No. of packets dropped: %d\n",num_packet_drop );
		printf("Drop percentage: %f\n",drop_percentage);
		sleep(1);   // sleep 1s. -> one second time step
		for (i = (q.front+1); i <= q.rear; ++i)
		{
			++q.items[i].delay;
		}
        start_t = time(NULL);
	}
	for (i = (q.front+1); i <= q.rear; ++i)
	{
		free(q.items[i].contents);
	}
	return 0;
}