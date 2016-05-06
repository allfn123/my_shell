
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE 256
//function handling_buf

static int old_in,old_out,flag=0;

void backup(int *,int *);
void re_in(char **);
void re_out(char **);
void re_all(int,int);
void redirection(int,char **);

int handling_buf(char *before,char segment_after[][BUF_SIZE])		//This function is used to separate the buf from myfifo into several independent segments.
{
	if(flag==0)
	{
		backup(&old_in,&old_out);
		flag++;
	}
	else
	{
		re_all(old_in,old_out);
	}

	char *tmp;
	int num_of_segment=0;					//num_of_segment is used to memorize the numbers of independent segments.
	strcpy(segment[0],strtok(before," "));
	while(tmp=strtok(NULL," "))				//segment is array of string that memorizes the containment of each segment.
	{
		num_of_segment++;
		strcpy(segment[num_of_segment],tmp);
	}
	
	if (num_of_segment==0 && strcmp(segment[0],"\n")==0)
		return num_of_segment+1;
	if (strcmp(segment[num_of_segment],"\n")==0)
		num_of_segment--;
	else
		segment[num_of_segment][strlen(segment[num_of_segment])-1]='\0';

	return num_of_segment+1;
}

void backup(int *old_in,int *old_out)
{
	*old_out=dup(STDOUT_FILENO);
	*old_in=dup(STDIN_FILENO);
}

void re_in(char arguments[][BUF_SIZE])
{
	int i=0,fd;
	while(strcmp(arguments[i],"<")!=0) i++;
	fd=open(arguments[i+1],O_CREAT | O_RDWR,0664);
	dup2(fd,STDIN_FILENO);
	close(fd);
}

void re_out(char arguments[][BUF_SIZE])
{
	int i=0,fd;
	while(strcmp(arguments[i],">")!=0) i++;
	fd=open(arguments[i+1],O_CREAT | O_RDWR | O_TRUNC ,0664);
	
	dup2(fd,STDOUT_FILENO);
	close(fd);
}

void re_all(int old_in,int old_out)
{
	dup2(old_in,STDIN_FILENO);
	dup2(old_out,STDOUT_FILENO);
}

void redirection(int type,char arguments[][BUF_SIZE])
{
	switch(type)
	{
		case 0:break;
		case 1:re_in(arguments);break;
		case 2:re_out(arguments);break;
		default:printf("Usage command <filename > filename");
	}
}


