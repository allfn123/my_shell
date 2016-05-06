#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include "my_link.h"

#define BUF_SIZE 256

void ls(char arguments[][BUF_SIZE],int num_of_arguments)
{
	struct dirent *dir_struct;
	DIR *dirp;
	node *filename_list;

	node *filename_list_sort_by_mtime;
	
	char path[10][BUF_SIZE];

	int a,l,i,t;		//bool--arguments
	a=l=i=t=0;
	if (strcmp(arguments[0],"ll")==0) l=1;

	int j=1,m=0,n;

	while(j<=num_of_arguments-1)
	{
		n=0;
		if(arguments[j][0]!='-')
		{
			if (arguments[j][0]=='~')					//solve the recognition of ~: /home/useaname/
			{
				strcpy(path[m],getenv("HOME"));
				strcat(path[m],arguments[j]);
				int k=strlen(getenv("HOME"));
				while(path[m][k]!='\0')
				{
					path[m][k]=path[m][k+1];
					k++;
				}
				j++;
				m++;
			}
			else 
			{
				strcpy(path[m],arguments[j]);
				j++;
				m++;
			}
			
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

		if (path[j][strlen(path[j])-1]=='/')			//display the directory which is listed
			printf("%s:\n",path[j]);
		else
			printf("%s/:\n",path[j]);

		if ((dirp=opendir(path[j]))==NULL)
		{
			perror("Failed to open directory");
			return ;
		}

		filename_list=create();
		if (t==0)
		{
			while ((dir_struct=readdir(dirp))!=NULL)
			{
			
				char s[256];
				strcpy(s,dir_struct->d_name);
				insert_by_name(filename_list,s);
			}
		}

		else
		{
			while ((dir_struct=readdir(dirp))!=NULL)
			{
			
				char s[256];
				strcpy(s,dir_struct->d_name);
				insert_by_time(path[j],filename_list,s);
			}
		}

		//filename create successfully

		display(path[j],filename_list,a,i,l,t);	

		nfree(filename_list);

		j++;
	}
	while ((closedir(dirp)==-1) && (errno==EINTR));
	return ;
}
