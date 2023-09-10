#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main(){
	struct passwd *pw;

	//pw = getpwuid(getuid());	// search by uid

	pw = getpwnam("sm");	// search by name


	printf("UID : %d\n",(int)pw->pw_uid);
	printf("Login Name : %s\n",pw->pw_name);
	printf("Gecos : %s\n",pw->pw_gecos);
}	


/* 
	char *pw_name
	char *pw_passwd
	uid_t pw_uid
	gid_t pw_gid
	char *pw_gecos
	char *pw_dir
	char *pw_shell
*/
