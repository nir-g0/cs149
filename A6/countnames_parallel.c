#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_INPUTS 100
#define MAX_NAME_SIZE 30

pthread_mutex_t tlock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tlock3 = PTHREAD_MUTEX_INITIALIZER;

char namesList[100][30];

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

int main(){

	table = (struct hashtable_t*)malloc(sizeof hashtable_t);
	
	printf("create first thread\n");
	pthread_create(&tid1,NULL,thread_runner,NULL);
	printf("create second thread\n");
	pthread_create(&tid2,NULL,thread_runner,NULL);
	printf("wait for first thread to exit\n");
	pthread_join(tid1,NULL);
	printf("first thread exited\n");
	printf("wait for second thread to exit\n");
	pthread_join(tid2,NULL);
	printf("second thread exited\n");
	//TODO print out the sum variable with the sum of all the numbers
	free(table);
	
	exit(0);
}//end main


/**********************************************************************
// function thread_runner runs inside each thread
**********************************************************************/
	
void* thread_runner(void* x, char* fileName){

	pthread_t me;
	
	me = pthread_self();
	
	printf("This is thread %ld (p=%p)\n",me,p);
	
	pthread_mutex_lock(&tlock2); // critical section starts
	
	if (p==NULL) {
		p = (THREADDATA*) malloc(sizeof(THREADDATA));
		p->creator=me;
	}
	
	pthread_mutex_unlock(&tlock2); // critical section ends
	if (p!=NULL && p->creator==me) {
		printf("This is thread %ld and I created THREADDATA %p\n",me,p);
	} else {
		printf("This is thread %ld and I can access the THREADDATA %p\n",me,p);
	}
	
	/**
	* //TODO implement any thread name counting functionality you need.
	* Assign one file per thread. Hint: you can either pass each argv filename as a
	thread_runner argument from main.
	* Or use the logindex to index argv, since every thread will increment the
	logindex anyway
	* when it opens a file to print a log message (e.g. logindex could also index
	argv)....
	* //Make sure to use any mutex locks appropriately
	*/
	// TODO use mutex to make this a start of a critical section
	// critical section starts
	char name[30];
   	fgets(name, 30, fp);
	int complete = feof(fp);
   	int line = 1;
   	//Iterates until reached end of file
  	while(!complete){

	  	if(name[0]== '\n'){
			fprintf(stderr, "Warning - File %s Line %d is empty\n", argv[argNum], line);
	  	}
	  	//search name function
	  	else{
	  		if (name[strlen(name)-1] == '\n'){
	  			name[strlen(name)-1] = '\0';
	  		}
	  		
	  		pthread_mutex_lock(&tlock3);
	  		
			hashAddCount(table, name);
	  		
	  		pthread_mutex_unlock(&tlock3);
	  		
		   	fgets(name, 30, fp);
		   	complete = feof(fp);
		   	line += 1;
		}
	}
	
	fclose(fp);
	if (p!=NULL && p->creator==me) {
		printf("This is thread %ld and I delete THREADDATA\n",me);
	/**
	* TODO Free the THREADATA object.
	* Freeing should be done by the same thread that created it.
	* See how the THREADDATA was created for an example of how this is done.
	*/
		free(p);
	} else {
		printf("This is thread %ld and I can access the THREADDATA\n",me);
	}
	// TODO critical section ends
	pthread_exit(NULL);
	//return NULL;
}






