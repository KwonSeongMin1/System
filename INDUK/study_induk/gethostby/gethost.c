#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main(){

	struct hostent *host;

	host = gethostbyname("www.naver.com");
	
	// h_name
	printf("host name : %s\n",host->h_name);
	
	// h_aliases
	for(int i=0;host->h_aliases[i];i++){
		printf("Aliases[%d] : %s\n",i,host->h_aliases[i]);
	}
	
	// h_addrtype
	printf("Address type : %s\n",(host->h_addrtype == AF_INET)?"AF_INET":"AF_INET6");

	// h_addr_list
	for(int i=0;host->h_addr_list[i];i++){
		printf("%02d : %s\n",i+1,inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
	}


	return 0;
}

