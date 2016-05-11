#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void my_touch(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1)
	{
		printf("Usage: touch [filename1] [filename2] ... [filenamen]\n");
		return;
	}

	else
	{
		int j=1,fd;
		while (j<num_of_arguments)
		{
			fd=open(arguments[j],O_CREAT | O_RDWR,0664);
			if (fd<0)
			{
				printf("File %s touch ",arguments[j]);
				perror("failed");
				j++;
				continue;
			}
			close(fd);
			j++;
		}
	}
}