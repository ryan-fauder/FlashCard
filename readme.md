#include<stdio.h>
#include<dirent.h>

int main(void)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}

// #include <stdio.h>
// #include <time.h>
// #include <string.h>
// #include <dirent.h>
// int main(void) {
//   printf("Hello World\n");
// 	time_t now;
// 	struct tm *now_tm;
// 	int hour, min, a;

// 	now = time(NULL);
// 	now_tm = localtime(&now);
// 	now_tm->tm_isdst = 3;
// 	hour = now_tm->tm_hour;
// 	min = now_tm->tm_min;
// 	printf("%d:%d", hour, a);
// 	return 0;
// }

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include <sys/types.h>
void make_directory(const char* name);
int main(void) {
	struct stat * s; 
	if(stat("config", s) == -1){
		make_directory("config");
	}
	return 0;
}

void make_directory(const char* name) {
   #ifdef __linux__
       mkdir(name, 777); 
   #else
       _mkdir(name);
   #endif
}