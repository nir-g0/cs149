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
	
	for(int i = 1; i < argc; i++){
		pid = fork();
		argNum = i;
		if(pid == 0){
			break;
		}
	}
	
	if(pid == 0){
	
		char *stdoutFile;
		char *stderrFile;
		
		sprintf(stdoutFile, "%d.txt", getpid());
		sprintf(stderrFile, "%d.err", getpid());
		
		outFileFD = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
		errFileFD = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
		
		dup2(outFileFD, 1);
		dup2(errFileFD, 2);
	}


	return 0;
}
