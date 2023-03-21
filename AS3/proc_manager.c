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
	char message[MAX_LINE_LENGTH];
	
	int pid;
	int argNum;
	
	int outFile;
	int errFile;
	
	char stdoutFile[MAX_LINE_LENGTH];
	char stderrFile[MAX_LINE_LENGTH];
	int i = 1;
	
	
	
	while(fgets(command, buffersize , stdin)){
	
		pid = fork();
		argNum = i;
		
		
		if(pid == 0){
		
			sprintf(stdoutFile, "%d.out", getpid());
			sprintf(stderrFile, "%d.err", getpid());
		
			outFile = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			errFile = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			
			if(dup2(outFile, STDOUT_FILENO) < 0){
				printf("DUP2 FAILED");
				exit(127);
			}
			if(dup2(errFile, STDERR_FILENO) < 0){
				printf("DUP2 FAILED");
				exit(127);
			}
						
			sprintf(message,"Starting command %d: child %d pid of parent %d\n", argNum, getpid(), getppid());
			write(outFile, message, strlen(message));
			
			exit(0);

		}
		else{
			while (wait ( NULL) != -1) {
				
				sprintf(stdoutFile, "%d.out", pid);
				sprintf(stderrFile, "%d.err", pid);
				
				FILE *fp;
				if((fp = fopen(stdoutFile, "a")) == NULL){
					printf("FILE OPEN ERROR");
				}
				
				sprintf(message,"Finished child %d pid of parent %d\n", pid, getpid());
				fprintf(fp,message,strlen(message));

				i++;
			}
		}
		
		
	}

	

	return 0;
}