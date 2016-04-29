#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "check_PATH.h"

#define BUF_SIZE 256

void judge(char segment[][BUF_SIZE],int n)				//This function is used to judge the first segment separated from the buf in the main function.
{

	char command_path[BUF_SIZE],command_name[BUF_SIZE];
	memset(command_path,0,sizeof(command_path));
	memset(command_name,0,sizeof(command_path));
	strcpy(command_name,segment[0]);
	check_PATH(command_name,command_path);	

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
	
	else if (command_path!=NULL)
	{
		printf("%s\n",command_path);
		return;
	}

	else if (access(segment[0],F_OK | X_OK)==0)
	{
		pid_t pid;
		int status;
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
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}

		else							//Parent program's 	
		{
			waitpid(pid,&status,0);
			return ;
		}
	}


	else
	{
		printf("%s: command not found.\n",segment[0]);	//If it is invalid command, tell the user.
		return;
	}
}
