/**
* Description: This program takes commands from stdin and tracks the command's: exit code, start, stop and errors
* Author name: Nir Guberman 
* Author email: Nir.guberman@sjsu.edu
* Last modified date: 3/22/23
* Creation date: 3/19/23
**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024
#define BUFFER_SIZE 30
#define MAX_ARGS 100

int main(int argc, char** argv){

	char command[BUFFER_SIZE];
	char message[MAX_LINE_LENGTH];
	char* args[MAX_ARGS];
	
	int pid;
	int argNum;
	
	int outFile;
	int errFile;
	
	char stdoutFile[MAX_LINE_LENGTH];
	char stderrFile[MAX_LINE_LENGTH];
	int i = 1;
	
	
	/*
	This while-loop awaits a user input in the stdin (terminal) and executes a command if the input is valid.
	The input can be a maximum of two words (one space), and the while loop is terminated when the user enters
	^D or ^z in the terminal. Otherwise, if an input is valid, two output files are created for the child process
	that was spawned for the command that was input.
	
	The first file will be PID.out --> logs the start and stoppage of the child process
	The second file will be PID.err --> logs the exit code of the process and any other errors in execution
	*/
	while(fgets(command, BUFFER_SIZE , stdin) != NULL){
		
		//create child process
		pid = fork();
		//check which command is being entered (third, fourth, etc..)
		argNum = i;
		
		//IN the child process:
		if(pid == 0){
			
			//Create the names of the output files using the PID of the current process
			sprintf(stdoutFile, "%d.out", getpid());
			sprintf(stderrFile, "%d.err", getpid());
		
			//Create the files
			outFile = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			errFile = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
			
			//Adjust file descriptors so for each process they were taking the proper stdin and stderr inputs
			if(dup2(outFile, STDOUT_FILENO) < 0){
				printf("DUP2 FAILED");
				exit(2);
			}
			if(dup2(errFile, STDERR_FILENO) < 0){
				printf("DUP2 FAILED");
				exit(2);
			}
					
			//First message in the PID.out file, tells user that the process is starting to run the command as
			//well as it's PID and parent's PID	
			sprintf(message,"Starting command %d: child %d pid of parent %d\n", argNum, getpid(), getppid());
			//write the message into PID.out
			write(outFile, message, strlen(message));
			
			//split the command received into multiple parameters in order for later execvp input
   			char* temp = strtok(command, " ");
   			char* temp2 = strtok(NULL, "\n");
   			
   			args[0] = temp;
   			args[1] = temp2;
   			args[2] = NULL;
    	
    			//execute the command using execvp
			execvp(args[0], args);
			
			//if execvp fails: print failure message to PID.err file and write the name of the command
			fprintf(stderr, "Failed Command Execution: %s", args[0]);
			if(args[1] != NULL){
				fprintf(stderr, " %s", args[1]);
			}
			//if execvp fails: exit with error 2 will be returned
			exit(2);

		}
		else{
			int exitCode; //stores exit status of child process
			
			//wait for the child process with specified pid to exit
			if (waitpid(pid, &exitCode, 0) != -1) {
				if(WIFEXITED(exitCode) != -1){

					//find the returned exit code of the child process and put it into "exitcode" variable
					exitCode = WEXITSTATUS(exitCode);
					
					//make file names for pid for later access (ASSUME FILES WERE CREATED)
					sprintf(stdoutFile, "%d.out", pid);
					sprintf(stderrFile, "%d.err", pid);
					
					FILE *fp;
					
					//checks if opening file with specifed name does not work: 
					if((fp = fopen(stdoutFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					
					//print message that the child process of the parent completed into child PID.out
					sprintf(message,"Finished child %d pid of parent %d\n", pid, getpid());
					fprintf(fp,message,strlen(message));
					
					//close file as it no longer needs to be accessed
					fclose(fp);
					
					//checks if opening file with specifed name does not work: 
					if((fp = fopen(stderrFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					//print exitcode returned from child into child PID.err
					sprintf(message,"Exited with exitcode = %d", exitCode);
					fprintf(fp, message, strlen(message));
					fclose(fp);

				}
			}
				
			//iterate to accurately count the amount of commands used
			i++;

		}
		
		
	}

	

	return 0;
}
