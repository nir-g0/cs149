#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t pid;
	for(int i = 0; i < 4; i++){
		pid = fork();
		if(pid == 0){
			break;
		}
	}
	
	if(pid == 0){
		printf("hello world from PID %d!\n", getpid());
	}
	
	return 0;
}
