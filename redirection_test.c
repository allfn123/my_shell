#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define BUF_SIZE 256

static int old_in,old_out;

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

int main()
{
	setbuf(stdout,NULL);
	setbuf(stdin,NULL);
	char arguments[5][BUF_SIZE]={"cd","<","k",">","t"};
	char a[BUF_SIZE];
	backup(&old_in,&old_out);
	redirection(2,arguments);
	redirection(1,arguments);
	scanf("%s",a);
	printf("%s",a);
	re_all(old_in,old_out);
	printf("%s",a);
	return 0;
}