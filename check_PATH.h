
#define BUF_SIZE 256

int check_PATH(char command_name[BUF_SIZE],char command_path[BUF_SIZE])
{
	char c[BUF_SIZE],*tmp;

	FILE *fp;

	if((fp=fopen("PATH","r"))==NULL)
	{
		//printf("Cannot find the PATH file\n");
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
