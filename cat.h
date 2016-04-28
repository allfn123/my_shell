#define BUF_SIZE 256


void filecopy(FILE *ifp,FILE *ofp)
{
	int count;
	while ((c=getc(ifp))!=EOF)
		putc(c,ofp);
}

void cat(char arguments[][BUF_SIZE],int num_of_arguments)
{
	FILE *fp;
	int i=1;

	if (num_of_arguments==1)
	{
		printf("Usage: cat [OPTION]... [FILE]...\n");
		return ;
	}
	else
	{
		while (i<num_of_arguments)
		{
			if((fp=open(arguments[i],O_RDONLY))==NULL)
			{
				printf("cat: %s:",arguments[i]);
				perror("");
				return;
			}
			else
			{
				filecopy(FILE )
			}
		}
	}
}