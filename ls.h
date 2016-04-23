#include <dirent.h>
#include <errno.h>
#include "my_link.h"
#define BUF_SIZE 256

void ls(char arguments[][BUF_SIZE],int num_of_arguments)
{
	struct dirent *dir_struct;
	DIR *dirp;
	node *filename_list;
	
	char path[10][BUF_SIZE];

	int a,l,i,t;		//bool--arguments
	a=l=i=t=0;

	int j=1,m=0,n;

	while(j<=num_of_arguments-1)
	{
		n=0;
		if(arguments[j][0]!='-')
		{
			strcpy(path[m],arguments[j]);
			j++;
			m++;
		}

		else 
		{
			n++;
			while(arguments[j][n]!='\0')
			{
				switch(arguments[j][n])
				{
					case 'a':a=1;n++;break;
					case 'l':l=1;n++;break;
					case 'i':i=1;n++;break;
					case 't':t=1;n++;break;
					default:printf("ls: -%c: invalid option\nusage: ls [-alit] [path]\n",arguments[j][n]);return;
				}

			}
			j++;
		}
	}

	if (m==0) 
		{
			strcpy(path[0],".");
			m++;
		}

	j=0;
	while(j<=m-1)
	{
		if ((dirp=opendir(path[j]))==NULL)
		{
			perror("Failed to open directory");
			return ;
		}

		filename_list=create();

		while ((dir_struct=readdir(dirp))!=NULL)
		{
			
			char s[256];
			strcpy(s,dir_struct->d_name);

			insert(filename_list,s);
		}
		j++;
		display(filename_list);	
		nfree(filename_list);
	}
	while ((closedir(dirp)==-1) && (errno==EINTR));
	return ;
}
