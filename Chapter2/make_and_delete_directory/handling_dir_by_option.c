#include <stdio.h>
#include <unistd.h>	// getopt(), rmdir()
#include <sys/stat.h>	// mkdir()
#include <stdlib.h>

int main(int argc, char* argv[]){
	
	int n;
	extern char *optarg;	// dir name
	
	if(argc<2){
		printf("missing command.\nTry \"-h\" to help command.\n");
	}


	while((n=getopt(argc,argv,"hr:m:"))!=-1){
		switch(n){
			case 'h':
				printf("-m <file name> : make directory.\n");
				printf("-r <file name> : remove directory.\n");
				break;
			case 'r':
				if(rmdir(optarg)==-1){
					perror(optarg);
					exit(1);
				}
				else{
					printf("Directory deleted successfully. %s\n",optarg);
				}
				break;
			case 'm':
				if(mkdir(optarg,0755)==-1){
					perror(optarg);
					exit(1);
				}
				else{
					printf("Directory created successfully. %s\n",optarg);
				}
				break;

		}
	}
}


