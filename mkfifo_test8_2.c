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

int main(void)
{
	setbuf(stdout,NULL);

	int fd;
	char buf[BUF_SIZE];
	char buf_after[20][BUF_SIZE];
	int n;
	umask(0);
	while (1)
	{
		fd=open(FIFO_NAME,O_RDONLY);
		memset(buf,0,sizeof(buf));
		
		read(fd,buf,BUF_SIZE);

		n=handling_buf(buf,buf_after);

		judge(buf_after,n);

		close(fd);
	}
	return 0;
}
