
#define BUF_SIZE 256
static int init=0;
static char init_path_backup[BUF_SIZE];
static 	char path_of_PATH[BUF_SIZE];

int check_PATH(char command_name[BUF_SIZE],char command_path[BUF_SIZE],char init_path[BUF_SIZE])
{
	char c[BUF_SIZE],*tmp;

	FILE *fp;

	if (init==0)
	{
		memset(path_of_PATH,0,sizeof(path_of_PATH));
		memset(init_path_backup,0,sizeof(init_path_backup));
		getcwd(path_of_PATH,BUF_SIZE);
		getcwd(init_path_backup,BUF_SIZE);
		strcat(path_of_PATH,"/");
		strcat(path_of_PATH,"PATH");
		init++;
	}

	strcpy(init_path,init_path_backup);
	
	if((fp=fopen(path_of_PATH,"r"))==NULL)
	{
		printf("Cannot find the PATH file\n");
		return -1;
	}

	while (!feof(fp))
	{
		if (fgets(c,BUF_SIZE,fp)!=NULL)
		{

			tmp=strtok(c," ");
			tmp[strlen(tmp)-1]='\0';

			if (strcmp(tmp,command_name)==0)
			{
				fgets(command_path,BUF_SIZE,fp);
				command_path[strlen(command_path)-1]='\0';
				fclose(fp);
				return 0;
			}
		}
	}
	fclose(fp);
	return -1;
}
