#include <string.h>
#include "judge_pipe.h"
#define BUF_SIZE 256

int pipe_check(char arguments[][BUF_SIZE],int num_of_arguments,char *FIFO_NAME)
{
	int i=0,f=0,j=0,flag;
	while(i<num_of_arguments)
	{
		if (strcmp(arguments[i],"|")==0)
		{
			f++;
			break;
		}
		else 
			i++;
	}
	if (f!=0)
		return 0;

	int num_of_arguments_1=i;
	char arguments_1[num_of_arguments_1][BUF_SIZE];
	while(j<num_of_arguments_1)
	{
		strcpy(arguments_1[j],arguments[j]);
		j++;
	}

	int num_of_arguments_2=num_of_arguments_1-i;
	char arguments_2[num_of_arguments_2][BUF_SIZE];
	j=0;
	while(j<num_of_arguments_2)
	{
		strcpy(arguments_2[j],arguments[num_of_arguments_1+j+1]);
		j++;
	}

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
		judge_pipe(arguments_1,num_of_arguments_1,FIFO_NAME);
		exit(EXIT_SUCCESS);
	}

	else							//Parent program's 	
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		judge_pipe(arguments_2,num_of_arguments_2,FIFO_NAME);
		//waitpid(pid,&status,0);
	}
	return 1;
}