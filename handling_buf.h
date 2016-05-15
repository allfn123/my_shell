
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE 256
//function handling_buf

int re_in(char []);
int re_out(char []);
int redirection(int,char [],int*);

int handling_buf(char *before,char segment_after[][BUF_SIZE],int *flag)		//This function is used to separate the buf from myfifo into several independent segments.
{
	

	char segment[40][BUF_SIZE];

	char *tmp;
	int num_of_segment=0;					//num_of_segment is used to memorize the numbers of independent segments.
	strcpy(segment[0],strtok(before," "));
	while(tmp=strtok(NULL," "))				//segment is array of string that memorizes the containment of each segment.
	{
		num_of_segment++;
		strcpy(segment[num_of_segment],tmp);
	}
	
	if (num_of_segment==0 && strcmp(segment[0],"\n")==0)
		num_of_segment++;
	else if (strcmp(segment[num_of_segment],"\n")==0)
		num_of_segment--;
	else
		segment[num_of_segment][strlen(segment[num_of_segment])-1]='\0';
	num_of_segment++;

	int i=0,n=0;
	while (i<num_of_segment)
	{
		if(strcmp(segment[i],">")!=0)
		{
			if(strcmp(segment[i],"<")!=0)
			{
				strcpy(segment_after[n],segment[i]);
				n++;
				i++;
			}
			else
			{
				if (i==num_of_segment-1)
				{
					return -1;
				}
				if (redirection(1,segment[++i],flag)==-1)
					return -1;
				i++;
			}
		}
		else
		{
			if (i==num_of_segment-1)
			{
				return -1;
			}
			if (redirection(2,segment[++i],flag)==-1)
					return -1;
			i++;
		}
	}
	return n;

}

void backup(int *old_in,int *old_out)
{
	*old_out=dup(STDOUT_FILENO);
	*old_in=dup(STDIN_FILENO);
}

int re_in(char arguments[])
{
	int fd;
	fd=open(arguments, O_RDONLY,0664);
	if (fd<0)
	{
		printf("Cannot open the redirection file %s",arguments);
		perror(" ");
		return -1;
	}
	dup2(fd,STDIN_FILENO);
	close(fd);
	return 0;
}

int re_out(char arguments[])
{
	int fd;
	fd=open(arguments,O_CREAT | O_RDWR | O_APPEND,0664);
	if (fd<0)
	{
		printf("Cannot open the redirection file %s",arguments);
		perror(" ");
		return -1;
	}
	dup2(fd,STDOUT_FILENO);
	close(fd);
	return 0;
}

void re_all(int old_in,int old_out)
{
	dup2(old_in,STDIN_FILENO);
	dup2(old_out,STDOUT_FILENO);
}

int redirection(int type,char arguments[],int *flag)
{
	int r;
	switch(type)
	{
		case 1:r=re_in(arguments);*flag=-1;return r;
		case 2:r=re_out(arguments);*flag=-1;return r;
		//default:printf("Usage command <filename > filename");
	}
}


