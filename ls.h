#include <dirent.h>
#include <errno.h>


void ls(char *path)
{
	struct dirent *dir_struct;
	DIR *dirp;
	
	//if (*path==NULL)
	if ((dirp=opendir(path))==NULL)
	{
		perror("Failed to open directory");
		return ;
	}

	while ((dir_struct=readdir(dirp))!=NULL)
	{
		if(dir_struct->d_name[0]!='.')
			printf("%s\t",dir_struct->d_name);
	}
	printf("\n");	
	while ((closedir(dirp)==-1) && (errno==EINTR));
	return ;
}
