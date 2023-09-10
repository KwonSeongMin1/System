#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	uid_t uid, euid;
	char *name;

	uid = getuid();	// real user ID
	euid = geteuid();	// effective user id
	name = getlogin();	// search /var/run/utmp

	printf("Login name = %s\nUID = %d\nEUID = %d\n",name,(int)uid,(int)euid);
}
