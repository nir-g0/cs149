#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_INPUT_LENGTH 1024
#define HASH_SIZE 101

typedef struct node_t{

	int pid;
	int commandNumber;
	char input[MAX_INPUT_LENGTH];
	double start;
	double finish;
	struct node_t* next;
	
} node;

typedef struct hashtable_t{

	node* nodeArray[HASH_SIZE + 1];

} hashtable;



int hashFunction(int pid){
	return pid % HASH_SIZE;
}

node* lookUp(hashtable* table, int pid){

	node *np;
	for (np = table->nodeArray[hashFunction(pid)]; np != NULL; np = np->next)
		if (pid == np->pid){
			return np; /* found */
		}
	return NULL; /* not found */
	
}

void hashtableInsert(hashtable* table, int pid, int cmdNum, char* cmd, double strt, double fin){
	
	node* bucketNode;
	bucketNode = lookUp(table, pid);
	
	if(bucketNode == NULL){
		printf("BUCKETNODE NULL FOR PID == %d\n", pid);
		
    	bucketNode = (node*)malloc(sizeof(node));
    	
    	int hashIndex = hashFunction(pid);
    	bucketNode->next = table->nodeArray[hashIndex];
    	table->nodeArray[hashIndex] = bucketNode;
    	
	}
	
	
    bucketNode->pid = pid;
    bucketNode->commandNumber = cmdNum;
    strcpy(bucketNode->input, cmd);
    bucketNode->start = strt;
    bucketNode->finish = fin;
	
}

void executeChildProc(char* messageString, char* cmd, int count){
	
	char* args[MAX_INPUT_LENGTH];
	
	char stdoutFile[MAX_INPUT_LENGTH];
	char stderrFile[MAX_INPUT_LENGTH];
	char message[MAX_INPUT_LENGTH];
	int outFile;
	int errFile;
		
	sprintf(stdoutFile, "%d.out", getpid());
	sprintf(stderrFile, "%d.err", getpid());
	
	//Create the files
	outFile = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
	errFile = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
		
	sprintf(message,"%sStarting command %d: child %d pid of parent %d\n", messageString, count, getpid(), getppid());
	write(outFile, message, strlen(message));
			
	char* temp = strtok(cmd, " ");
   	char* temp2 = strtok(NULL, "\n");
   			
   	args[0] = temp;
   	args[1] = temp2;
   	args[2] = NULL;

   			
   	execvp(args[0], args);
   	fprintf(stderr, "Failed Command Execution: %s", args[0]);
   	exit(2); 
}

int main(int argc, char** argv){


	int pidArray[HASH_SIZE + 1];
	struct timespec start, finish;
	
	int count = 1;
	int indexCount = 0;
	hashtable* table = (hashtable*)malloc(sizeof(hashtable));
	char* cmd = (char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
	int procPID;
	double duration;
	
	while(fgets(cmd, MAX_INPUT_LENGTH, stdin) != NULL){
		
		clock_gettime(CLOCK_MONOTONIC, &start);
		procPID = fork();
		
		//Create the names of the output files using the PID of the current process		

		if(procPID == 0){
   			executeChildProc("",cmd, count);
		}
		else{
			pidArray[indexCount] = procPID;
			int exitCode;
			if (waitpid(procPID, &exitCode, 0) != -1) {
				if(WIFEXITED(exitCode) != -1){
					clock_gettime(CLOCK_MONOTONIC, &finish);
					char stdoutFile[MAX_INPUT_LENGTH];
					char stderrFile[MAX_INPUT_LENGTH];
					char message[MAX_INPUT_LENGTH];
				
					sprintf(stdoutFile, "%d.out", procPID);
					sprintf(stderrFile, "%d.err", procPID);
					
					FILE *fp;
					
					//checks if opening file with specifed name does not work: 
					if((fp = fopen(stdoutFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					
					sprintf(message,"Finished child %d pid of parent %d\n", procPID, getpid());
					fprintf(fp,message,strlen(message));


					hashtableInsert(table, procPID, count, cmd, start.tv_sec, finish.tv_sec);
					duration = (finish.tv_nsec - start.tv_nsec)/1000000000.0 + (finish.tv_sec - start.tv_sec);
					
					sprintf(message,"Finished at %ld, runtime duration %.4f\n", finish.tv_sec,duration);
					fprintf(fp,message,strlen(message));
					
					fclose(fp);
					
					if((fp = fopen(stderrFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					//print exitcode returned from child into child PID.err
					sprintf(message,"Exited with exitcode = %d\n", exitCode);
					fprintf(fp, message, strlen(message));
					
					
					if(duration <= 2){
						sprintf(message,"spawning too fast\n");
						fprintf(fp, message, strlen(message));
						indexCount++;
						fclose(fp);
					}
					else{
						indexCount++;
						fclose(fp);
						int temp = procPID;

						while(duration > 2){
							sprintf(message, "%s", cmd);
							procPID = fork();
							clock_gettime(CLOCK_MONOTONIC, &start);
							if(procPID == 0){																
								executeChildProc("RESTARTING\n", message, count);
							}
							else{
								pidArray[indexCount] = procPID;
								if (waitpid(procPID, &exitCode, 0) != -1) {
									if(WIFEXITED(exitCode) != -1){
										clock_gettime(CLOCK_MONOTONIC, &finish);
										duration = (finish.tv_nsec - start.tv_nsec)/1000000000.0 + (finish.tv_sec - start.tv_sec);
										sprintf(stdoutFile, "%d.out", procPID);
										sprintf(stderrFile, "%d.err", procPID);
										
										if((fp = fopen(stdoutFile, "a")) == NULL){
											printf("FILE OPEN ERROR");
										}
										
										sprintf(message,"Finished child %d pid of parent %d\n", procPID, getpid());
										fprintf(fp,message,strlen(message));


									    hashtableInsert(table, procPID, count, cmd, start.tv_sec, finish.tv_sec);
										
										sprintf(message,"Finished at %ld, runtime duration %.4f\n", finish.tv_sec,duration);
										fprintf(fp,message,strlen(message));
										
										fclose(fp);									
										
										if((fp = fopen(stderrFile, "a")) == NULL){
											printf("FILE OPEN ERROR");
										}
										//print exitcode returned from child into child PID.err
										sprintf(message,"RESTARTING\nExited with exitcode = %d\n", exitCode);
										fprintf(fp, message, strlen(message));	
										
										fclose(fp);
										
										indexCount++;
									}
								}
							}
						}
					}
				} 
			}
		}
		count++;
	} 
	
	
	
	for(int i = 0; i < indexCount; i++){
		node* temp = lookUp(table, pidArray[i]);
		if(temp == NULL){
			printf("NULL ERROR\n");
		}else{
			free(temp);
		}
	} 
	
	free(table);
	free(cmd);
	
	return 0;
}


