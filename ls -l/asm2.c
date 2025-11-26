#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>

int main(int argc, char *argv[])
{
	char *dirpath;
	DIR *dp = NULL;
	struct dirent *ent;
	struct stat st;

	if(argc != 2)
	{
		printf("Directory path is not mentioned...\n");
		printf("Run as : %s <dir path>\n", argv[0]);
		exit(1);
	}
	
	dirpath = argv[1];

	chdir(dirpath);

	//1. open the directory stream
	dp = opendir(dirpath);
	if(dp == NULL)
	{
		printf("Directory is not opened...\n");
		exit(1);
	}

	//2. read entries one by one and print their information
	printf("Directory content : \n");
	while((ent = readdir(dp)) != NULL)
	{
		stat(ent->d_name, &st);
		printf("%u %u %lu %u %u %u %s\n", ent->d_type, st.st_mode, st.st_nlink, st.st_uid, st.st_gid, st.st_size, ent->d_name);
	}
	//3. close the directory stream
	closedir(dp);

	return 0;
}















