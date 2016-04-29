#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_stat(char *path,char *filename)
{
	struct stat st;

	char d_path[256];
	strcpy(d_path,path);

	if (d_path[strlen(d_path)-1]=='/')
		strcat(d_path,filename);
	else 
	{
		strcat(d_path,"/");
		strcat(d_path,filename);
	}

	if (lstat(d_path,&st))
	{
		perror("Failed to get stat from files");
		return ;
	}

	if (S_ISDIR(st.st_mode))
		printf("d");
	else if (S_ISFIFO(st.st_mode))
		printf("p");
	else if (S_ISLNK(st.st_mode))
		printf("l");
	else if (S_ISBLK(st.st_mode))
		printf("b");
	else if (S_ISCHR(st.st_mode))
		printf("c");
	else if (S_ISSOCK(st.st_mode))
		printf("s");
	else
		printf("-");


	(st.st_mode & S_IRUSR) ? printf("r") : printf("-");
	(st.st_mode & S_IWUSR) ? printf("w") : printf("-");
	(st.st_mode & S_IXUSR) ? printf("x") : printf("-");
	(st.st_mode & S_IRGRP) ? printf("r") : printf("-");
	(st.st_mode & S_IWGRP) ? printf("w") : printf("-");
	(st.st_mode & S_IXGRP) ? printf("x") : printf("-");
	(st.st_mode & S_IROTH) ? printf("r") : printf("-");
	(st.st_mode & S_IWOTH) ? printf("w") : printf("-");
	(st.st_mode & S_IXOTH) ? printf("x") : printf("-");

	printf(".");

	printf("%3lu\t",st.st_nlink);


	struct passwd *pwd;
	pwd=getpwuid(st.st_uid);
	printf("%s\t",pwd->pw_name);

	struct group *grp;
	grp=getgrgid(st.st_gid);
	printf("%s\t",grp->gr_name);

	printf("%10ld  ",st.st_size);

	char time[64];
	strftime(time,sizeof(time),"%b %e %H:%M",localtime(&st.st_mtime));
	printf("%s  ",time);	

}

void print_inode(char *path,char *filename)
{
	struct stat st;

	char d_path[256];
	strcpy(d_path,path);

	if (d_path[strlen(d_path)-1]=='/')
		strcat(d_path,filename);
	else 
	{
		strcat(d_path,"/");
		strcat(d_path,filename);
	}

	if (lstat(d_path,&st))
	{
		perror("Failed to get stat from files");
		return ;
	}

	printf("%*lu ",10,st.st_ino);
}

void print_link(char *path,char *filename)
{
	struct stat st;

	char d_path[256];
	strcpy(d_path,path);
	char buf[1024];

	if (d_path[strlen(d_path)-1]=='/')
		strcat(d_path,filename);
	else 
	{
		strcat(d_path,"/");
		strcat(d_path,filename);
	}

	if (lstat(d_path,&st))
	{
		perror("Failed to get stat from files");
		return ;
	}

	memset(buf,0,1024);
	if(readlink(d_path,buf,1024)!=-1)
		printf(" -> %s",buf);
	else return;
}

unsigned long int get_mtime(char *path,char *filename)
{
	struct stat st;

	char d_path[256];
	strcpy(d_path,path);

	if (d_path[strlen(d_path)-1]=='/')
		strcat(d_path,filename);
	else 
	{
		strcat(d_path,"/");
		strcat(d_path,filename);
	}

	if (lstat(d_path,&st))
	{
		perror("Failed to get time from files");
		return -1;
	}

	return st.st_mtime;
}
