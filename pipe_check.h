#include <string.h>
#define BUF_SIZE 256

int pipe_check(char arguments[][BUF_SIZE],int *num_of_arguments)
{
	int i=0,f=0,j=0,flag;
	while(i<*num_of_arguments)
	{
		if (strcmp(arguments[i],"|")==0)
		{
			f++;
			break;
		}
		else 
			i++;
	}
	if (f==0)
		return 0;

	

	pid_t pid;
	int status;
	int fd[2];
	if(pipe(fd))
	{
		perror("Failed to create pipe");
		return -1;
	}

	pid=fork();
	if (pid<0)
	{
		perror("Failed to fork");		
		return -1;
	}

	else if (pid==0)
	{
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		*num_of_arguments=i;
		return 2;
	}

	else							//Parent program's 	
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		while(j<*num_of_arguments-i)
		{
			strcpy(arguments[j],arguments[i+j+1]);
			j++;
		}
		*num_of_arguments-=i;
		return 3;

		//waitpid(pid,&status,0);
	}
	return 1;
}