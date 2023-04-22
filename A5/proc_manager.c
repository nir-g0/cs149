#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <timer.h>

#define MAX_INPUT_LENGTH 1024
#define HASH_SIZE 101

typedef struct node_t{

	int pid;
	int commandNumber;
	char input[MAX_INPUT_LENGTH];
	double start;
	double finish;
	
	
} node;

typedef struct hashtable_t{

	node* nodeArray[HASH_SIZE + 1];

} hashtable;



int hashFunction(int pid){
	return pid % HASH_SIZE;
}

node* hashTable lookUp(hashtable* table, int pid){

	struct nlist *np;
	for (np = table[hash(s)]; np != NULL; np = np->next)
		if (pid == np->pid)
			return np; /* found */
	return NULL; /* not found */
	
}

void hashtableInsert(hashtable* table, int pid, int cmdNum, char* cmd, double strt, double fin){

	int bucket = hashFunction(pid);
	node* bucketNode = table->buckets[bucket];
	
	while
}



int main(int argc, char** argv){

	return 0;
}


