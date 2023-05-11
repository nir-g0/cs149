/**
* Description: This program reads inputs from two files and counts the amount of times a name appears in both files together. This program
		utilizes multi threading to efficiently achieve this as well as a hashtable to optimaly store and access data.
* Author name: Nir Guberman 
* Author email: Nir.guberman@sjsu.edu
* Last modified date: 5/10/23
* Creation date: 5/06/23
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define MAX_INPUTS 100
#define MAX_NAME_SIZE 30

//mutex locks to ensure exclusive data access
pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;


void* thread_runner(void*);
pthread_t tid1, tid2;

//struct points to the thread that created the object.
//This is useful for you to know which is thread1. Later thread1 will also deallocate.
struct THREADDATA_STRUCT
{
	pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p = NULL;

//variable for indexing of messages by the logging function.
int logindex=0;
int *logip = &logindex;

typedef struct node_t{

	char name[MAX_NAME_SIZE];
	int count;
	struct node_t* next;
	
} node;

//struct for hashtable data structure. Stores nodes as buckets for quick data access
typedef struct hashtable_t{
	node* nodeArray[MAX_INPUTS + 1];
} hashtable_t;

hashtable_t* table;

//variable for indexing of messages by the logging function.
int hashFunction(char* input){
	// Calculate hash value by taking the modulus of the input as an integer with the hash table size
	unsigned long inputAsNum = 0;
   	 for (int i = 0; input[i]; i++)
        	inputAsNum += input[i];
    	return inputAsNum % MAX_INPUTS;
}

// Function to lookup a node in the hash table
node* lookUp(char* name){
    // Traverse the linked list starting from the head of the hash table array
    int hashIndex = hashFunction(name);
    if(table->nodeArray[hashIndex] == NULL){ //if node at index does not exist
    	return NULL;
    }
    return table->nodeArray[hashIndex]; //if node at index exists, return that node
    
}

// Function to insert a node into the hash table
void hashAddCount(char* name){
	
    node* bucketNode;
    bucketNode = lookUp(name); // Look up the node in the hash table
    
    if(bucketNode == NULL){ // If the node is not found, create a new node and insert it into the hash table
        bucketNode = (node*)malloc(sizeof(node));
        int hashIndex = hashFunction(name);
        strcpy(bucketNode->name, name);
        bucketNode->count = 1;
        bucketNode->next = table->nodeArray[hashIndex]; // Set the next pointer of the new node to the current head of the linked list
        table->nodeArray[hashIndex] = bucketNode; // Set the head of the linked list to the new node
    }else{
    	bucketNode->count += 1;
    }
}

char* arg1;
char* arg2;

int main(int argc, char** argv){
	
	//allocate memory for the hashtable/////
	table = malloc(sizeof(hashtable_t));
    	if (table == NULL) {
        	printf("Failed to allocate memory for the hash table\n");
     		return 1;
   	}
   	memset(table, 0, sizeof(hashtable_t));
   	/////////////////////////////////////////
   	
	arg1 = argv[1];
	arg2 = argv[2];

	logindex = 1;
	
	printf("create first thread\n");
	pthread_create(&tid1,NULL,&thread_runner,arg1);
	printf("create second thread\n");
	pthread_create(&tid2,NULL,&thread_runner,arg2);
	printf("wait for first thread to exit\n");
	pthread_join(tid1,NULL);
	printf("first thread exited\n");
	printf("wait for second thread to exit\n");
	pthread_join(tid2,NULL);
	printf("second thread exited\n");
	
	//print out the names and their counts, also free the node so memory is not being wasted
   	printf("======================================== Name Counts ========================================\n");
	for(int i = 0; i < MAX_INPUTS; i++){
		node* currNode = table->nodeArray[i];
		if(currNode != NULL){
			printf("%s: %d\n", currNode->name, currNode->count);
			while (currNode != NULL) {
        			node* nextNode = currNode->next;
        			free(currNode);
        			currNode = nextNode;
    			}
		}
	}
    	printf("=============================================================================================\n");
    	
    	//free memory allocated for hashtable
	free(table);
	exit(0);
}//end main


//function for printing log message to console
void printLog(pthread_t me){
	
    printf("\nLogindex %d, thread %ld, PID %d, ", (*logip), me, getpid());
    time_t t = time(NULL);
    struct tm *timeinfo = localtime(&t);
    char timeString[80];
    strftime(timeString, 80, "%d/%m/%Y %I:%M:%S %p", timeinfo);
    printf("%s: ", timeString);
}

//function to count line number inside of the file that is empty

	
void* thread_runner(void* x){
	int line = 1;
	//convert argument to char string
	char* fileName = (char*)x;
	
	pthread_t me;
	me = pthread_self();

	pthread_mutex_lock(&tlock2); // critical section starts
	if (p == NULL) {
	    p = (THREADDATA*) malloc(sizeof(THREADDATA));
	    p->creator = me;
	}
	pthread_mutex_unlock(&tlock2); // critical section ends

	pthread_mutex_lock(&tlock1);
	if (p != NULL && p->creator == me) {
	    printLog(me);
	    printf("This is thread %ld and I created THREADDATA %p\n", me, p);
	    (*logip)++;
	} else {
            printLog(me);
	    printf("This is thread %ld and I can access the THREADDATA %p\n", me, p);
	    (*logip)++;
	}
	
	printLog(me);
	printf("Opened %s\n", fileName);
	(*logip)++;
	pthread_mutex_unlock(&tlock1);
	
	//open file 
	FILE* fp;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stdout, "Error - failed to open file %s\n", fileName);
		pthread_exit(NULL);
	}

	
	//read through file and count how often name appears
	char name[30];
	fgets(name, 30, fp);
	int complete = feof(fp);
	// Iterates until reached end of file
	while (!complete) {
		if (name[0] == '\n') {
		    fprintf(stderr, "\nWarning - File %s line %d is empty\n\n", fileName, line);
		} else {
			
		    //replace the final character with null char for accurate string comparison
		    if (name[strlen(name) - 1] == '\n') {
			name[strlen(name) - 1] = '\0';
		    }
		    
		    //add count or add name to hashtable
		    hashAddCount(name);
		}
		fgets(name, 30, fp);
		complete = feof(fp);
		line++;
	}
	fclose(fp);

	pthread_mutex_lock(&tlock1); // critical section starts
	printLog(me);
	if (p != NULL && p->creator == me) {
	    printf("This is thread %ld and I delete THREADDATA\n", me);
	    free(p); // free the THREADDATA object
	    p = NULL;
	} else {
	    printf("This is thread %ld and I can access the THREADDATA\n", me);
	}
	(*logip)++;
	pthread_mutex_unlock(&tlock1); // critical section ends

	pthread_exit(NULL);

}






