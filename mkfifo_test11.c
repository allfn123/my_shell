#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "judge.h"
#include "handling_buf.h"
#define BUF_SIZE 256

static int old_in,old_out,flag=0;

void backup(int *,int *);
void re_all(int,int);

int main(int argc,char *argv[])
{
	
	if (argc==1)
	{
		printf("Usage: %s [FIFO_NAME]\n",argv[0]);
		exit(1);
	}

	else
	{
		if (mkfifo(argv[1],S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)==-1)
		{
			perror("Failed to new a FIFO");
			exit(1);
		}

		setbuf(stdout,NULL);
		umask(0);

		int fd,n;
		char buf[BUF_SIZE];
		char pwd[BUF_SIZE];
		char FIFO_NAME[BUF_SIZE];
		memset(FIFO_NAME,0,sizeof(FIFO_NAME));
		getcwd(FIFO_NAME,BUF_SIZE);
		strcat(FIFO_NAME,"/");
		strcat(FIFO_NAME,argv[1]);
		
		while (1)
		{

			if(flag==0)
			{
				backup(&old_in,&old_out);
				flag=1;
			}
			else if(flag==-1)
			{
				re_all(old_in,old_out);
				flag=1;
			}

			memset(pwd,0,sizeof(pwd));
			getcwd(pwd,BUF_SIZE);
			printf("[Trevor's shell %s]$ ",pwd);

			fd=open(FIFO_NAME,O_RDONLY);
			memset(buf,0,sizeof(buf));
		
			read(fd,buf,BUF_SIZE);
			printf("%s",buf);

			char *buf_after[BUF_SIZE];
			n=handling_buf(buf,buf_after,&flag);

			judge(buf_after,n,FIFO_NAME);
		
			close(fd);
		}
		return 0;
	}

	
}
