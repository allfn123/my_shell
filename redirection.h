void redirection(int type,char arguments[][BUF_SIZE],int num_of_arguments)
{
	switch(type)
	{
		case 0:break;
		case 1:{
			int i=0,fd;
			while(arguments[i]!=">") i++;
			fd=open(arguments[i+1],O_CREAT | O_RDWR);
			pud2(fd,1);
			close(fd);
		}
	}
}