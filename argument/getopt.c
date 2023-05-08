#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	int n,a=0,b=0,c=0;
	extern char *optarg;
	extern int optind;

	while((n=getopt(argc,argv,"abc:"))!=-1){
		switch(n){
			case 'a':
				a = 1;
				break;
			case 'b':
				b = 1;
				break;
			case 'c':
				c = 1;
				printf("optarg : %s\n",optarg);
				break;
			case '?':
				printf("Unknown flag : %c", optopt);
				break;
		}
	}

	if(a) printf("flag : a\n");
	if(b) printf("flag : b\n");
	if(c) printf("flag : c, argc : %s\n",optarg);
}

