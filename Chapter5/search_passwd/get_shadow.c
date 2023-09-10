#include <shadow.h>
#include <stdio.h>



// sudo ./<program> 
int main(){
	struct spwd *spw;

	spw = getspnam("sm");
	printf("Login name : %s\n",spw->sp_namp);
	printf("passwd : %s\n",spw->sp_pwdp);
	printf("Last change : %ld\n",spw->sp_lstchg);
}

