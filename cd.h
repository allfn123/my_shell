#define BUF_SIZE 256

void cd(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments==1 || (arguments[1][0]=='~' && strlen(arguments[1])==1)) 
	{
		if (chdir(getenv("HOME"))==-1)
		{
			printf("cd: %s",getenv("HOME"));
			perror(" ");
			return ;
		}
		printf("\n");
	}
	else if (arguments[1][0]=='~' && strlen(arguments[1])>1)
	{
		if (chdir(getenv("HOME"))==-1)
		{
			printf("cd: %s",getenv("HOME"));
			perror(" ");
			return ;
		}
		char relative_path[BUF_SIZE];
		memset(relative_path,0,sizeof(relative_path));
		int i=0;
		while(i<strlen(arguments[1])-2)
		{
			relative_path[i]=arguments[1][i+2];
			i++;
		}
		if (chdir(relative_path)==-1)
		{
			printf("cd: %s",arguments[1]);
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
