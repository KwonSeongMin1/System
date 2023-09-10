#include <stdio.h>
#include <time.h>	//	time() & ctime()
#include <sys/types.h>
#include <sys/time.h>	//	gettimeofday()

char *output = "%j %D %A %C %T";


int main(){

	time_t tloc;	// use time() & ctime(0
	struct timeval tv;	// use gettimeofday()
	struct tm *tm;	// use strftime()
	char buf[257];

	time(&tloc);	// 1970.01.01.00:00:00 ~ now .s
	gettimeofday(&tv, NULL);

	printf("use time() sec : %d\n",(int)tloc);
	printf("use gettimeofday() sec : %d\nmicro sec : %d\n",(int)tv.tv_sec,(int)tv.tv_usec);
	printf("use ctime date : %s\n",ctime(&tloc));

	tm = localtime(&tloc);	// second -> tm structure
	strftime(buf,sizeof(buf),output,tm);
	printf("strftime : %s\n",buf);
}

