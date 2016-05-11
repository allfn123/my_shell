#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

void mkdir(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1 || num_of_arguments>2)
	{
		printf("Usage: mkdir [directionname]");
		return ;
	}
	else
	{
		if (mkdir(segment[1],S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH)<0)
		{
			perror("mkdir failed");
			return ;
		}
	}
}