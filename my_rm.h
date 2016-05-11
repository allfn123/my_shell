#include <stdio.h>

void my_rm(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1)
	{
		printf("Usage: rm [filename1] [filename2] ... [filenamen]\n");
		return;
	}

	else
	{
		int j=1;
		while (j<num_of_arguments)
		{
			if (remove(arguments[j])<0)
			{
				printf("File %s remove ",arguments[j]);
				perror("failed");
				j++;
				continue;
			}
			j++;
		}
	}
}