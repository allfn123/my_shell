#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX 255
#endif

int pwd(void)
{
	char current_work_path[PATH_MAX];
	if (getcwd(current_work_path,PATH_MAX)==NULL)
	{
		perror("Failed to get current working directory\n");
		return 1;
	}

	printf("Current working directory: %s\n",current_work_path);
	return 0;
}
