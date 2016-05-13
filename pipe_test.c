#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "judge.h"
#include "handling_buf.h"

void re_in(char []);
void re_out(char []);
void redirection(int,char [],int*);

int main()
{
	pid_t pid;
	int status;
	int i1,i2;
	int fd[2];
	if(pipe(fd))
	{
		perror("Create pipe failed");
		exit(1);
	}


	pid=fork();
	if (pid<0)
	{
		perror("Failed to fork\n");		
		exit(1);
	}

	else if (pid==0)
	{
		close(fd[1]);
		dup2(fd[0],STDIN_FILENO);
		if (execvp("./add",NULL)==-1)
		{
			perror("Exec error");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}

	else							//Parent program's 	
	{
		scanf("%d %d",&i1,&i2);
		close(fd[0]);
		dup2(fd[1],STDOUT_FILENO);
		printf("%d %d",i1,i2);
		//waitpid(pid,&status,0);
	}

	printf("bingo");
	return 0;
}

void backup(int *old_in,int *old_out)
{
	*old_out=dup(STDOUT_FILENO);
	*old_in=dup(STDIN_FILENO);
}

void re_in(char arguments[])
{
	int fd;
	fd=open(arguments,O_CREAT | O_RDWR,0664);
	dup2(fd,STDIN_FILENO);
	close(fd);
}

void re_out(char arguments[])
{
	int fd;
	fd=open(arguments,O_CREAT | O_RDWR | O_TRUNC ,0664);
	dup2(fd,STDOUT_FILENO);
	close(fd);
}

void re_all(int old_in,int old_out)
{
	dup2(old_in,STDIN_FILENO);
	dup2(old_out,STDOUT_FILENO);
}

void redirection(int type,char arguments[],int *flag)
{
	switch(type)
	{
		case 1:re_in(arguments);*flag=-1;break;
		case 2:re_out(arguments);*flag=-1;break;
		default:printf("Usage command <filename > filename");
	}
}