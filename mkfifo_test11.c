#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "judge.h"
#include "handling_buf.h"
#define FIFO_NAME "myfifo"
#define BUF_SIZE 256

int main(int argc,char *argv[])
{
	if (argc==1)
	{
		printf("Usage: %s [FIFO_NAME]\n",argv[0]);
		exit(1);
	}

	else
	{
		if (mkfifo(argv[1],S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))
		{
			perror("Failed to new a FIFO");
			exit(1);
		}

		setbuf(stdout,NULL);

		int fd;
		char buf[BUF_SIZE];
//	char buf_after[20][BUF_SIZE];


		char pwd[BUF_SIZE],pwd_origin[BUF_SIZE];
		memset(pwd_origin,0,sizeof(pwd));
		getcwd(pwd_origin,BUF_SIZE);
		strcat(pwd_origin,"/");
		strcat(pwd_origin,"myfifo");


		int n;
		umask(0);
		while (1)
		{
			memset(pwd,0,sizeof(pwd));
			getcwd(pwd,BUF_SIZE);
			printf("[Trevor's shell %s]$ ",pwd);

			//fd=open(pwd_origin,O_RDONLY);
			fd=open(argv[1],O_RDONLY);
			memset(buf,0,sizeof(buf));
		
			read(fd,buf,BUF_SIZE);

			char *buf_after[BUF_SIZE];
			printf("%s",buf);

			n=handling_buf(buf,buf_after);

			judge(buf_after,n);
		
			close(fd);
		}
		return 0;
	}

	
}
