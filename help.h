#include <stdio.h>
#include <string.h>
#define BUF_SIZE 256

static char help_file[BUF_SIZE];
static int init_help=0;

void filecopy(FILE *,FILE *);

void help(char * init_path)
{
	if (init_help==0)
	{
		strcpy(help_file,init_path);
		strcat(help_file,"/");
		strcat(help_file,"help_text");
		init_help++;
	}
	FILE *fp;

	if((fp=fopen(help_file,"r"))==NULL)
	{
		perror("Cannot find the text of help");
		return;
	}
	else
	{
		filecopy(fp,stdout);
		fclose(fp);
		return;
	}
}

void filecopy(FILE *ifp,FILE *ofp)
{
	int c;
	while ((c=getc(ifp))!=EOF)
		putc(c,ofp);
}