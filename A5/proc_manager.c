/**
* Description: This program takes command in through stdin and executes them. After execution, the program writes
			   to a file, telling the duration of execution. If execution takes too long, the process will be restarted.
			   The output files will have a helpful message telling the user if the process was restarted or if it spawned
			   too fast.
* Author name: Nir Guberman 
* Author email: Nir.guberman@sjsu.edu
* Last modified date: 4/26/23
* Creation date: 4/21/23
**/

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

// Function to compute the hash value
int hashFunction(int pid){
	// Calculate hash value by taking the modulus of the PID with the hash table size
    return pid % HASH_SIZE; 
}

// Function to lookup a node in the hash table
node* lookUp(hashtable* table, int pid){

    node *np;
    // Traverse the linked list starting from the head of the hash table array
    for (np = table->nodeArray[hashFunction(pid)]; np != NULL; np = np->next)    
    if (pid == np->pid){ // If the PID matches, return the node
            return np; 
        }
    return NULL; // Return NULL if the node is not found in the hash table
    
}

// Function to insert a node into the hash table
void hashtableInsert(hashtable* table, int pid, int cmdNum, char* cmd, double strt, double fin){

    node* bucketNode;
    bucketNode = lookUp(table, pid); // Look up the node in the hash table
    
    if(bucketNode == NULL){ // If the node is not found, create a new node and insert it into the hash table
        bucketNode = (node*)malloc(sizeof(node));
        int hashIndex = hashFunction(pid);
        bucketNode->next = table->nodeArray[hashIndex]; // Set the next pointer of the new node to the current head of the linked list
        table->nodeArray[hashIndex] = bucketNode; // Set the head of the linked list to the new node
    }
    // Update the fields of the bucket node
    bucketNode->pid = pid;
    bucketNode->commandNumber = cmdNum;
    strcpy(bucketNode->input, cmd);
    bucketNode->start = strt;
    bucketNode->finish = fin;
}

//executes the child process
void executeChildProc(char* messageString, char* cmd, int count){
	
	char* args[MAX_INPUT_LENGTH];
	
	char stdoutFile[MAX_INPUT_LENGTH];
	char stderrFile[MAX_INPUT_LENGTH];
	char message[MAX_INPUT_LENGTH];
	int outFile;
	int errFile;
	
	//name files based on pid
	sprintf(stdoutFile, "%d.out", getpid());
	sprintf(stderrFile, "%d.err", getpid());
	
	//Create the files
	outFile = open(stdoutFile, O_RDWR | O_CREAT | O_APPEND, 0777);
	errFile = open(stderrFile, O_RDWR | O_CREAT | O_APPEND, 0777);
		
	//write message to file
	sprintf(message,"%sStarting command %d: child %d pid of parent %d\n", messageString, count, getpid(), getppid());
	write(outFile, message, strlen(message));
			
	char* temp = strtok(cmd, " ");
   	char* temp2 = strtok(NULL, "\n");
   			
   	//break the command up into arguments
   	args[0] = temp;
   	args[1] = temp2;
   	args[2] = NULL;

   	//execute command
   	execvp(args[0], args);
   	fprintf(stderr, "Failed Command Execution: %s", args[0]);
   	exit(2); 
}

int main(int argc, char** argv){

	int pidArray[HASH_SIZE + 1];
	struct timespec start, finish;
	
	int count = 1;
	int indexCount = 0;
	
	//hashtable to store data
	hashtable* table = (hashtable*)malloc(sizeof(hashtable));
	//dynamically allocated command string
	char* cmd = (char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
	
	int procPID;
	double duration;
	
	//while inputs available
	while(fgets(cmd, MAX_INPUT_LENGTH, stdin) != NULL){
		
		//start time
		clock_gettime(CLOCK_MONOTONIC, &start);
		procPID = fork();

		if(procPID == 0){
		//child process, execute command
   			executeChildProc("",cmd, count);
		}
		else{
			//save the index of the current PID for freeing allocated memory later
			pidArray[indexCount] = procPID;
			int exitCode;
			//wait for process to complete
			if (waitpid(procPID, &exitCode, 0) != -1) {
				if(WIFEXITED(exitCode) != -1){
					//stop clock on completion
					clock_gettime(CLOCK_MONOTONIC, &finish);
					char stdoutFile[MAX_INPUT_LENGTH];
					char stderrFile[MAX_INPUT_LENGTH];
					char message[MAX_INPUT_LENGTH];
					
					//name files based on child PID
					sprintf(stdoutFile, "%d.out", procPID);
					sprintf(stderrFile, "%d.err", procPID);
					
					FILE *fp;
					
					//open stdoutFile
					if((fp = fopen(stdoutFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					
					//write message to stdouFile
					sprintf(message,"Finished child %d pid of parent %d\n", procPID, getpid());
					fprintf(fp,message,strlen(message));

					//insert known data to hashtable and calculate duration of process
					hashtableInsert(table, procPID, count, cmd, start.tv_sec, finish.tv_sec);
					duration = (finish.tv_nsec - start.tv_nsec)/1000000000.0 + (finish.tv_sec - start.tv_sec);
					
					//write runtime to stdoutFile
					sprintf(message,"Finished at %ld, runtime duration %.4f\n", finish.tv_sec,duration);
					fprintf(fp,message,strlen(message));
					
					fclose(fp);
					
					//open stderrFile
					if((fp = fopen(stderrFile, "a")) == NULL){
						printf("FILE OPEN ERROR");
					}
					
					//print exitcode returned from child into child PID.err
					sprintf(message,"Exited with exitcode = %d\n", exitCode);
					fprintf(fp, message, strlen(message));
					
					
					//if the child process took less than two seconds...
					if(duration <= 2){
						sprintf(message,"spawning too fast\n");
						//print spawning to fast to stderr
						fprintf(fp, message, strlen(message));
						indexCount++;
						fclose(fp);
					}
					else{
						//we need to restart process
						indexCount++;
						fclose(fp);
						int temp = procPID;
						//keep restarting process until duration becomes less than two or is killed before 2
						while(duration > 2){
							sprintf(message, "%s", cmd);
							procPID = fork();
							//start timer
							clock_gettime(CLOCK_MONOTONIC, &start);
							if(procPID == 0){			
								//execute new child process with old command that took too long													
								executeChildProc("RESTARTING\n", message, count);
							}
							else{
								//when process completes... (same as earlier)
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
										
										//restart process if duration > 2
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
	
	//free nodes from hashtable
	for(int i = 0; i < indexCount; i++){
		node* temp = lookUp(table, pidArray[i]);
		if(temp == NULL){
			printf("NULL ERROR\n");
		}else{
			free(temp);
		}
	} 
	
	//free hash table and command input
	free(table);
	free(cmd);
	
	return 0;
}


