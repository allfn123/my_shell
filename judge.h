#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "my_mkdir.h"
#include "my_rmdir.h"
#include "my_touch.h"
#include "my_rm.h"
#include "check_PATH.h"
#include "help.h"
#include "text_cp.h"
#include "my_echo.h"
#include "pipe_check.h"

#define BUF_SIZE 256

void My_return(int P);

void judge(char segment[][BUF_SIZE],int n,char *FIFO_NAME)				//This function is used to judge the first segment separated from the buf in the main function.
{
	int P;
	P=pipe_check(segment,&n);
	if (P==1 || P==-1)
	{
		return;
	}

	char command_path[BUF_SIZE],command_name[BUF_SIZE],init_path[BUF_SIZE];
	int t;
	memset(command_path,0,sizeof(command_path));
	memset(command_name,0,sizeof(command_name));
	memset(init_path,0,sizeof(init_path));
	strcpy(command_name,segment[0]);
	t=check_PATH(command_name,command_path,init_path);

	char *argv[BUF_SIZE];
	int k=0;

	while(k<n)
	{
		//memset(argv[k],0,sizeof(argv[k]));
		argv[k]=segment[k];
		k++;
	}
	argv[n]=NULL;

	if (strcmp(segment[0],"exit")==0) 			//It judges whether the command is built-in command, executable file in current directory or
	{							//invalid command.
		if (n!=1)
		{
			printf("Usage: exit\n");
			My_return(P);
			return ;
		}
		if (remove(FIFO_NAME)==-1)
		{
			perror("FIFO cannot be deleted:");
		}
		printf("exit\n");				//If it is a built-in command, it calls the built-in function to finish the task.
		exit(0);                                	//If it is a executable file, it forks the executable file.
	}    

	if (strcmp(segment[0],"help")==0 || strcmp(segment[0],"?")==0)
	{
		help(init_path);
		My_return(P);
		return;
	}          

	else if (strcmp(segment[0],"\n")==0 && n==1)
	{
		printf("\n");
		My_return(P);
		return ;
	}

	else if (strcmp(segment[0],"pwd")==0)
	{
		if (n!=1)
		{
			printf("Usage: pwd\n");  
			My_return(P);
			return ;
		}
		pwd();
		My_return(P);
		return ;
	}
		        
                                 
	else if (strcmp(segment[0],"cd")==0)			
	{
		cd(segment,n);
		My_return(P);						
		return;						
	}
	
	else if (strcmp(segment[0],"ls")==0 || strcmp(segment[0],"ll")==0) 	
	{
		ls(segment,n);
		My_return(P);
		return;
	}

	else if (strcmp(segment[0],"mkdir")==0)
	{
		my_mkdir(segment,n);
		My_return(P);
		return;
	}

	else if (strcmp(segment[0],"rmdir")==0)
	{
		my_rmdir(segment,n);
		My_return(P);
		return;
	}

	else if (strcmp(segment[0],"touch")==0)
	{
		my_touch(segment,n);
		My_return(P);
		return;
	}

	else if (strcmp(segment[0],"rm")==0)
	{
		my_rm(segment,n);
		My_return(P);
		return;
	}

	else if (strcmp(segment[0],"cp")==0)
	{
		text_cp(segment,n);
		My_return(P);
		return;
	}	

	else if (strcmp(segment[0],"echo")==0)
	{
		my_echo(segment,n);
		My_return(P);
		return ;
	}

	else if (t==0 && command_path!=NULL)
	{
		if (access(command_path,F_OK | X_OK)==0)
		{
			pid_t pid;
			int status;
			pid=fork();

			if (pid<0)
			{
				perror("Failed to fork\n");
				My_return(P);		
				return;
			}

			else if (pid==0)
			{
				if (execvp(command_path,argv)==-1)
				{
					perror("Exec error");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}

			else							//Parent program's 	
			{
				waitpid(pid,&status,0);
				My_return(P);
				return ;
			}
		}
		else
		{
			printf("%s: command not found.\n",segment[0]);
			My_return(P);
			return;
		}
		My_return(P);
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
			My_return(P);
			return;
		}

		if (pid==0)
		{

			if (execvp(segment[0],argv)==-1)
			{
				perror("Exec error");
				printf("May be ./[filename]?\n");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}

		else							//Parent program's 	
		{
			waitpid(pid,&status,0);
			My_return(P);
			return ;
		}
	}


	else
	{
		printf("%s: command not found.\n",segment[0]);	//If it is invalid command, tell the user.
		My_return(P);
		return;
	}
}

void My_return(int P)
{
	if (P==2) exit(1);
	if (P==3) 
	{
		return;
	}
}
