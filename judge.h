#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "cat.h"

#define BUF_SIZE 256

void judge(char segment[][BUF_SIZE],int n)				//This function is used to judge the first segment separated from the buf in the main function.
{
	if (strcmp(segment[0],"exit")==0) 			//It judges whether the command is built-in command, executable file in current directory or
	{							//invalid command.
		if (n!=1)
		{
			printf("Usage: exit\n");
			return ;
		}
		printf("exit\n");				//If it is a built-in command, it calls the built-in function to finish the task.
		exit(0);                                	//If it is a executable file, it forks the executable file.
	}              

	else if (strcmp(segment[0],"\n")==0 && n==1)
	{
		printf("\n");
		return ;
	}

	else if (strcmp(segment[0],"pwd")==0)
	{
		if (n!=1)
		{
			printf("Usage: pwd\n");  
			return ;
		}
		pwd();
		return ;
	}
		        
                                 
	else if (strcmp(segment[0],"cd")==0)			
	{
		cd(segment,n);						
		return;						
	}
	
	else if (strcmp(segment[0],"ls")==0) 	
	{
		ls(segment,n);
		return;
	}

	else if (strcmp(segment[0],"cat")==0)
	{

		cat(segment,n);
		return ;
	}
	
	else if(access(segment[0],F_OK | X_OK)==0)
	{
		pid_t pid;
		pid=fork();

		if (pid<0)
		{
			perror("Failed to fork\n");		
			return;
		}

		else if (pid==0)
		{

			if (execlp(segment[0],NULL)==-1)
			{
				perror("Exec error");
				exit(1);
			}
			exit(1);
		}

		else							//Parent program's 	
			return ;
	}

	else
	{
		printf("%s: command not found.\n",segment[0]);	//If it is invalid command, tell the user.
		return;
	}
}
