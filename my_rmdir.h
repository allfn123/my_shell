#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

void my_rmdir(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1)
	{
		printf("Usage: mkdir [directionname]\n");
		return ;
	}
	else
	{
		int j=1;
		while (j<num_of_arguments)
		{
			if (rmdir(arguments[j])<0)
			{
				printf("Directory %s ",arguments[j]);
				perror("remove failed");
				j++;
				continue;
			}
			j++;
		}
	}
}