#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_INPUTS 100
#define MAX_NAME_SIZE 30

typedef struct node_t{

	char[MAX_NAME_SIZE] name;
	int count;
	struct node_t* next;
	
} node;

int hashFunction(char* input){

	unsigned long inputAsNum = 0;

   	 for (int i = 0; input[i]; i++)
        	inputAsNum += input[i];

    	return inputAsNum % MAX_INPUTS;
}

node* lookUp(char* name){

    node *np;
    // Traverse the linked list starting from the head of the hash table array
    for (np = table->nodeArray[hashFunction(name)]; np != NULL; np = np->next)    
   	 if (pid == np->pid){ // If the PID matches, return the node
            return np; 
        }
    return NULL; // Return NULL if the node is not found in the hash table
    
}

// Function to insert a node into the hash table
void hashAddCount(char* name){

    node* bucketNode;
    bucketNode = lookUp(table, name); // Look up the node in the hash table
    
    if(bucketNode == NULL){ // If the node is not found, create a new node and insert it into the hash table
        bucketNode = (node*)malloc(sizeof(node));
        int hashIndex = hashFunction(pid);
        strcpy(bucketNode->name, name);
        bucketNode->count = 1;
        bucketNode->next = table->nodeArray[hashIndex]; // Set the next pointer of the new node to the current head of the linked list
        table->nodeArray[hashIndex] = bucketNode; // Set the head of the linked list to the new node
    }else{
    	bucketNode->count += 1;
    }

}




