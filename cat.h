#include <stdio.h>
#define BUF_SIZE 256

void filecopy(FILE *,FILE *);

int main(int argc,char *argv[])
{
	
	FILE *fp;

	if (argc==1)
	{
		filecopy(stdin, stdout);
	}
	else
	{
		while (--argc>0)
		{
			if((fp=fopen(*++argv,O_RDONLY))==NULL)
			{
				printf("cat: %s:",arguments[i]);
				perror("");
				continue;
			}
			else
			{
				filecopy(fp,stdout);
				fclose(fp);
				continue;
			}
		}
		
		return 0;
	}
}

void filecopy(FILE *ifp,FILE *ofp)
{
	int c;
	while ((c=getc(ifp))!=EOF)
		putc(c,ofp);
}