#include <stdio.h>

void my_echo(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1)
	{
		printf("Usage: echo [string1] [string2] ... [stringn]\n");
		return ;
	}
	else 
	{
		int i=1;
		while(i<num_of_arguments)
		{
			printf("%s\n",arguments[i]);
			i++;
		}
	}
}