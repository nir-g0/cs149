#include <stdio.h>

int main(int argc, char **argv){

	if(argc == 0){
		return 0;
	}
	
	char commands[100][30] = {};
	pid_t pid;
	int argNum;
	int outFileFD;
	int errFileFD;
	char *stdoutFile;
	char *stderrFile;
	
	for(int i = 1; i < argc; i++){
		pid = fork();
		argNum = i;
		
		
		sprintf(stdoutFile, "%d.txt", pid);
		sprintf(stderrFile, "%d.err", pid);
		

		outFileFD = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
		errFileFD = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			
		if(pid == 0){
		
			dup2(outFileFD, 1);
			dup2(errFileFD, 2);
			
			printf("Starting command %d: child %d pid of parent %d", argNum, getpid(), getppid());

		}
		else{
			wait();
		}
		
		
	}

	

	return 0;
}
