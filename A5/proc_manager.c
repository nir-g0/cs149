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
		if (pid == np->pid)
			return np; /* found */
	return NULL; /* not found */
	
}

node* hashtableInsert(hashtable* table, int pid, int cmdNum, char* cmd, double strt, double fin){

	node* bucketNode = lookUp(table, pid);
	if(bucketNode == NULL){
		bucketNode = (node*)malloc(sizeof(node));
		int hashIndex = hashFunction(pid);
		bucketNode->next = table->nodeArray[hashIndex];
		table->nodeArray[hashIndex] = bucketNode;
	}
	else{
		free(bucketNode);
	}
	
	bucketNode->pid = pid;
	bucketNode->commandNumber = cmdNum;
	strcpy(bucketNode->input, cmd);
	bucketNode->start = strt;
	bucketNode->finish = fin;
	
	return bucketNode;
	
}



int main(int argc, char** argv){
	
	int count = 0;
	hashtable* table;
	char* cmd = (char*)malloc(MAX_INPUT_LENGTH*sizeof(char));
	
	while(fgets(cmd, MAX_INPUT_LENGTH, stdin)) != NULL){
		cmd[sizeof(cmd) - 1] = '\0';
	}
	
	
	return 0;
}


