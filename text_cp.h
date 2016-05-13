#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void text_cp(char arguments[][BUF_SIZE],int num_of_arguments)
{
	if (num_of_arguments!=3)
	{
		printf("Usage: cp [source file name] [target file name]\n");
		return;
	}
	else 
	{
		int fd[2];
		char buf[100];
        int nbytes;//每次读取的字节个数
        int write_ret;
        /*读文件，写文件*/
        
		fd[0]=open(arguments[1],O_RDONLY);
		if (fd[0]<0)
		{
			perror("Failed to open the source file");
			return;
		}
		
		fd[1]=open(arguments[2],O_CREAT | O_WRONLY | O_TRUNC,0664);
		if (fd[1]<0)
		{
			perror("Failed to open the target file");
			close(fd[0]);
			return;
		}

        while(nbytes = read(fd[0],buf,100))/*每次从源文件读取100字节数据到buf*/
        {
            write_ret = write(fd[1],buf,nbytes);/*将buf中的数据写入目标文件*/
            if(write_ret < 0)
            {
                perror("Write error");
                return;
            }
        }

        close(fd[0]);
        close(fd[1]);

	}
}