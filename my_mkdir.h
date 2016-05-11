#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

void my_mkdir(char arguments[][BUF_SIZE],int num_of_arguments)
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
			if (mkdir(arguments[j],S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH)<0)
			{
				printf("%s ",arguments[j]);
				perror("mkdir failed");
				j++;
				continue;
			}
			j++;
		}
	}
}