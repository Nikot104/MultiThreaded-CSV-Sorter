#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			printf("%s\n\n", path);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } 
	else
	{
		if(strstr(entry->d_name, ".csv"))
		{
			snprintf(path, sizeof(path), "%s/%s",name, entry->d_name);
            printf("%*s- %s\n", indent, "", path);
		}
        }
	/*
	char bapo[5];
	memcpy(bapo, &entry->d_name[strlen(entry->d_name)-4],4);
	printf("\n also the substring ext is: %s \n",bapo);
	
	if(strcmp(bapo,".csv") == 0)
	{
		printf("We found a .csv file, attempting sort");
	
		if(fork() == 0)
		{
			printf("I am the child and it is my duty to sort");
			return;
		}
	
	}
	*/
    }
    closedir(dir);
}

int main(void) {
    listdir(".", 0);
    return 0;
}
