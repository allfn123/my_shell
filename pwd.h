
int pwd(void)
{
	char * current_work_path;
	long max_size_path;

	if ((max_size_path=pathconf(".",_PC_PATH_MAX))==-1)
	{
		perror("Failed to determine the pathname length");
		return 1;
	}

	if ((current_work_path=(char *) malloc(max_size_path))==NULL)
	{
		perror("Failed to allocate space for pathname");
		return 1;
	}

	if (getcwd(current_work_path,max_size_path)==NULL)
	{
		perror("Failed to get current working directory");
		return 1;
	}

	printf("Current working directory: %s\n",current_work_path);
	return 0;
}
