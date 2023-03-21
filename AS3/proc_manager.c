#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024

int main(){

	
	
	int buffersize = 30;
	char command[buffersize];
	int pid;
	int argNum;
	int outFileFD;
	int errFileFD;
	char stdoutFile[MAX_LINE_LENGTH];
	char stderrFile[MAX_LINE_LENGTH];
	int i = 1;
	
	while(fgets(command, buffersize , stdin)){
	
		pid = fork();
		argNum = i;
		
		
		if(pid == 0){
		

		
			sprintf(stdoutFile, "%d.out", getpid());
			sprintf(stderrFile, "%d.err", getpid());
		
			outFileFD = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			errFileFD = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			
			
			
			if(dup2(outFileFD, 1) < 0){
				printf("DUP2 FAILED");
				exit(127);
			}
			if(dup2(errFileFD, 2) < 0){
				printf("DUP2 FAILED");
				exit(127);
			}
			
			char message[MAX_LINE_LENGTH];
			sprintf(message,"Starting command %d: child %d pid of parent %d\n", argNum, getpid(), getppid());
			write(outFileFD, message, strlen(message));
			
			exit(0);

			
		}
		else{
			while (wait ( NULL) != -1) {

				printf("Ending command %d\n", argNum);
				i++;
			}
		}
		
		
	}

	

	return 0;
}
