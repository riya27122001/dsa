#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Expressions to be evaluated are to be give

int main(int argc, char const *argv[])
{
	char expr[50], val[5];
	double stack[20];
	int i,j,k,flg,flg1,l,len;
	char *check;
	
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
            
            check=fgets (expr , 50 , file);
            while(check != NULL)
        		{
        			
        			len=strlen(expr);
        			expr[len]=' ';	//Adding space character to extract tags
        			expr[len+1]='\0';
        			
        			k=0; //Stack element counter
        			
        			
        			i=0; //Expression character counter
        			
        			while(i!=strlen(expr))
        			{
        				j=0;
        				//Storing tags
        				while((expr[i]!=' ')&&(expr[i]!='\n'))
        				{
        					val[j]=expr[i];
        					++j; ++i;
        				}
        				i=i+1;
        				val[j]='\0';
        				if (expr[i]=='\0')
        				{
        					break;
        				}
        				
        				flg=0;
        				//Illegal tags for fractional exponential
        				for (l = 0; l < j; ++l)
        				{
        					if(val[l]=='e')
        					{
        						flg++;
        					}
        					if((flg==1)&&(val[l]=='.'))
        					{
        						flg1++;
        					}
        					
        				}
        				if((flg==1)&&(flg1==1))
        				{
        					expr[len-1]='\0'; //To remove new line character
        					printf("%s: ",expr); //Printing result stored as remaining element in stack
        					printf("Invalid expr. Illegal tag: %s\n",val);

        					break;
        				}
        				//Operand tags
        				if ((strcmp(val,"+")!=0)&&(strcmp(val,"-")!=0)&&(strcmp(val,"*")!=0)&&(strcmp(val,"/")!=0))
        				{
        					stack[k]= atof(val);
        					
        					k++;
        				}
        				//Operator tags
        				else if(strcmp(val,"+")==0)
        				{
        					if(k<2)
        					{
        						expr[len-1]='\0'; //To remove new line character
        						printf("%s: ",expr); //Printing result stored as remaining element in stack
        						printf(" Invalid expr. “+” does not have enough operands\n"); //Less than two operands
        						break;
        					}
        					else
        					{
        						stack[k-2]=stack[k-1]+stack[k-2];
        						k=k-1;
        					}
        				}
        				else if(strcmp(val,"-")==0)
        				{
        					if(k<2)
        					{
        						expr[len-1]='\0'; //To remove new line character
        						printf("%s: ",expr); //Printing result stored as remaining element in stack
        						printf(" Invalid expr. “-” does not have enough operands\n"); //Less than two operands
        						break;
        					}
        					else
        					{
        						stack[k-2]=stack[k-1]-stack[k-2];
        						k=k-1;
        					}
        				}
        				else if(strcmp(val,"*")==0)
        				{
        					if(k<2)
        					{
        						expr[len-1]='\0'; //To remove new line character
        						printf("%s: ",expr); //Printing result stored as remaining element in stack
        						printf(" Invalid expr. “*” does not have enough operands\n"); //Less than two operands
        						break;
        					}
        					else
        					{
        						stack[k-2]=stack[k-2]*stack[k-1];
        						k=k-1;
        					}
        				}
        				else if(strcmp(val,"/")==0)
        				{
        					if(k<2)
        					{
        						expr[len-1]='\0'; //To remove new line character
        						printf("%s: ",expr); //Printing result stored as remaining element in stack
        						printf(" Invalid expr. “/” does not have enough operands\n"); //Less than two operands
        						break;
        					}
        					else
        					{
        						stack[k-2]=stack[k-2]/stack[k-1];
        						k=k-1;
        					}
        				}
        				
        				
        				
        			}
        			
        		expr[len-1]='\0'; //To remove new line character
        		printf("%s: %f\n",expr,stack[0]); //Printing result stored as remaining element in stack
        		expr[0]='\0';
        		check=fgets (expr , 50 , file);	//Getting new expression
        		}
        }

    }
	return 0;
}