#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define MAX_INPUTS 100
#define MAX_NAME_SIZE 30

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock4 = PTHREAD_MUTEX_INITIALIZER;


void* thread_runner(void*);
pthread_t tid1, tid2;

struct THREADDATA_STRUCT
{
	pthread_t creator;
};

typedef struct THREADDATA_STRUCT THREADDATA;

THREADDATA* p=NULL;

int logindex=0;
int *logip = &logindex;

typedef struct node_t{

	char name[MAX_NAME_SIZE];
	int count;
	struct node_t* next;
	
} node;

typedef struct hashtable_t{
	node* nodeArray[MAX_NAME_SIZE + 1];
} hashtable_t;

struct hashtable_t* table;

int hashFunction(char* input){

	unsigned long inputAsNum = 0;

   	 for (int i = 0; input[i]; i++)
        	inputAsNum += input[i];

    	return inputAsNum % MAX_INPUTS;
}

node* lookUp(struct hashtable_t* table, char* name){

    node *np;
    // Traverse the linked list starting from the head of the hash table array
    for (np = table->nodeArray[hashFunction(name)]; np != NULL; np = np->next)    
   	 if (strcmp(name, np->name) == 0){ // If the PID matches, return the node
            return np; 
        }
    return NULL; // Return NULL if the node is not found in the hash table
    
}

// Function to insert a node into the hash table
void hashAddCount(struct hashtable_t* table, char* name){

    node* bucketNode;
    bucketNode = lookUp(table, name); // Look up the node in the hash table
    
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
char namesList[100][30];
int nameCount;

int main(int argc, char** argv){
	
	
	table = (struct hashtable_t*)malloc(sizeof(hashtable_t));
	arg1 = argv[1];
	arg2 = argv[2];
	nameCount = 0;
	logindex = 1;

	printf("create first thread\n");
	pthread_create(&tid1,NULL,thread_runner,arg1);
	printf("create second thread\n");
	pthread_create(&tid2,NULL,thread_runner,arg2);
	printf("wait for first thread to exit\n");
	pthread_join(tid1,NULL);
	printf("first thread exited\n");
	printf("wait for second thread to exit\n");
	pthread_join(tid2,NULL);
	printf("second thread exited\n");
	
   	printf("----------------------------------------------\n");
	for(int i = 0; i < nameCount; i++){
		node* currNode = lookUp(table, namesList[i]);
		printf("%s: %d\n", currNode->name, currNode->count);
	}
    	printf("----------------------------------------------\n");	
	
	
	free(table);
	
	exit(0);
}//end main


/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
	
void printLog(pthread_t me){

    printf("\nLogindex %d, thread %ld, PID %d, ", logindex, me, getpid());
    time_t t = time(NULL);
    struct tm *timeinfo = localtime(&t);
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y %I:%M:%S %p", timeinfo);
    printf("%s: ", buffer);
}
	
void* thread_runner(void* x) {
    char* fileName = (char*)x;

    pthread_t me;
    me = pthread_self();
    
    pthread_mutex_lock(&tlock2); // critical section starts
    if (p == NULL) {
        p = (THREADDATA*)malloc(sizeof(THREADDATA));
        p->creator = me;
    }
    pthread_mutex_unlock(&tlock2); // critical section ends
    
    THREADDATA* thread_data = p;
    if (thread_data != NULL && thread_data->creator == me) {
        printf("This is thread %ld and I created THREADDATA %p\n", me, thread_data);
    } else {
        printf("This is thread %ld and I can access the THREADDATA %p\n", me, thread_data);
    }
    
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error - failed to open file %s\n", fileName);
        pthread_exit(NULL);
    }
    
    char name[30];
    fgets(name, 30, fp);
    int complete = feof(fp);
    // Iterates until reached end of file
    while (!complete) {
        if (name[0] == '\n') {
            fprintf(stderr, "Warning - line is empty\n");
        } else {
            if (name[strlen(name) - 1] == '\n') {
                name[strlen(name) - 1] = '\0';
            }
            pthread_mutex_lock(&tlock3);
            
            if(lookUp(table, name) == NULL){
            	 strcpy(namesList[nameCount],name);
            	 nameCount++;
            }
            hashAddCount(table, name);
            
            pthread_mutex_unlock(&tlock3);
            fgets(name, 30, fp);
            complete = feof(fp);
        }
    }
    fclose(fp);
    
    if (thread_data != NULL && thread_data->creator == me) {
        printf("This is thread %ld and I delete THREADDATA\n", me);
        free(thread_data);
    } else {
        printf("This is thread %ld and I can access the THREADDATA\n", me);
    }
    

    pthread_exit(NULL);
}






