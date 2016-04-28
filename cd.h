#define BUF_SIZE 256

void cd(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1 || arguments[1][0]=='~') 
	{
		if (chdir(getenv("HOME"))==-1)
		{
			printf("cd: %s",getenv("HOME"));
			perror(" ");
			return ;
		}
		printf("\n");
	}
	else
	{

		if (chdir(arguments[1])==-1)
		{
			printf("cd: %s",arguments[1]);
			perror(" ");
			return ;
		}
		printf("\n");
	}
}
