#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>


typedef struct node{
	char* line;
	int index;
	struct node* right;
} node_t;

/**
 * TRACE_NODE_STRUCT is a linked list of
 *pointers to function identifiers
 *TRACE_TOP is the head of the list is the top of the stack
*/
struct TRACE_NODE_STRUCT {
  char* functionid;                // ptr to function identifier (a function name)
  struct TRACE_NODE_STRUCT* next;  // ptr to next frama
};
typedef struct TRACE_NODE_STRUCT TRACE_NODE;
static TRACE_NODE* TRACE_TOP = NULL;       // ptr to the top of the stack


/* --------------------------------*/
/* function PUSH_TRACE */
/* 
 * The purpose of this stack is to trace the sequence of function calls,
 * just like the stack in your computer would do. 
 * The "global" string denotes the start of the function call trace.
 * The char *p parameter is the name of the new function that is added to the call trace.
 * See the examples of calling PUSH_TRACE and POP_TRACE below
 * in the main, make_extend_array, add_column functions.
**/
void PUSH_TRACE(char* p)          // push p on the stack
{
  TRACE_NODE* tnode;
  static char glob[]="global";

  if (TRACE_TOP==NULL) {

    // initialize the stack with "global" identifier
    TRACE_TOP=(TRACE_NODE*) malloc(sizeof(TRACE_NODE));

    // no recovery needed if allocation failed, this is only
    // used in debugging, not in production
    if (TRACE_TOP==NULL) {
      printf("PUSH_TRACE: memory allocation error\n");
      exit(1);
    }

    TRACE_TOP->functionid = glob;
    TRACE_TOP->next=NULL;
  }//if

  // create the node for p
  tnode = (TRACE_NODE*) malloc(sizeof(TRACE_NODE));

  // no recovery needed if allocation failed, this is only
  // used in debugging, not in production
  if (tnode==NULL) {
    printf("PUSH_TRACE: memory allocation error\n");
    exit(1);
  }//if

  tnode->functionid=p;
  tnode->next = TRACE_TOP;  // insert fnode as the first in the list
  TRACE_TOP=tnode;          // point TRACE_TOP to the first node

}/*end PUSH_TRACE*/

/* --------------------------------*/
/* function POP_TRACE */
/* Pop a function call from the stack */
void POP_TRACE()    // remove the top of the stack
{
  TRACE_NODE* tnode;
  tnode = TRACE_TOP;
  TRACE_TOP = tnode->next;
  free(tnode);

}/*end POP_TRACE*/



/* ---------------------------------------------- */
/* function PRINT_TRACE prints out the sequence of function calls that are on the stack at this instance */
/* For example, it returns a string that looks like: global:funcA:funcB:funcC. */
/* Printing the function call sequence the other way around is also ok: funcC:funcB:funcA:global */
char* PRINT_TRACE()
{
  int depth = 50; //A max of 50 levels in the stack will be combined in a string for printing out.
  int i, length, j;
  TRACE_NODE* tnode;
  static char buf[100];

  if (TRACE_TOP==NULL) {     // stack not initialized yet, so we are
    strcpy(buf,"global");   // still in the `global' area
    return buf;
  }

  /* peek at the depth(50) top entries on the stack, but do not
     go over 100 chars and do not go over the bottom of the
     stack */

  sprintf(buf,"%s",TRACE_TOP->functionid);
  length = strlen(buf);                  // length of the string so far
  for(i=1, tnode=TRACE_TOP->next;
                        tnode!=NULL && i < depth;
                                  i++,tnode=tnode->next) {
    j = strlen(tnode->functionid);             // length of what we want to add
    if (length+j+1 < 100) {              // total length is ok
      sprintf(buf+length,":%s",tnode->functionid);
      length += j+1;
    }else                                // it would be too long
      break;
  }
  return buf;
} /*end PRINT_TRACE*/

// -----------------------------------------
// function REALLOC calls realloc
// TODO REALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F reallocated the memory segment at address A to a new size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* REALLOC(void* p,int t,char* file,int line)
{
	
	p = realloc(p,t);
	fprintf(stdout, "File \"%s\", line %d, function %s reallocated the memory segment at address %p to a new size %d\n",file,line,PRINT_TRACE(),p,t);
	return p;
}

// -------------------------------------------
// function MALLOC calls malloc
// TODO MALLOC should also print info about memory usage.
// TODO For this purpose, you need to add a few lines to this function.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F allocated new memory segment at address A to size S"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void* MALLOC(int t,char* file,int line)
{
	void* p;
	p = malloc(t);
	fprintf(stdout, "File \"%s\", line %d, function %s allocated new memory segment at address %p to size %d\n",file,line,PRINT_TRACE(),p,t);
	return p;
}

// ----------------------------------------------
// function FREE calls free
// TODO FREE should also print info about memory usage.
// For instance, example of print out:
// "File mem_tracer.c, line X, function F deallocated the memory segment at address A"
// Information about the function F should be printed by printing the stack (use PRINT_TRACE)
void FREE(void* p,char* file,int line)
{
	fprintf(stdout, "File \"%s\",line %d,function %s deallocated the memory segment at address %p\n",file,line,PRINT_TRACE(),p);
	free(p);
}

#define realloc(a,b) REALLOC(a,b,__FILE__,__LINE__)
#define malloc(a) MALLOC(a,__FILE__,__LINE__)
#define free(a) FREE(a,__FILE__,__LINE__)

//This function dynamically increases the size of the array to hold more space
char** extend_array(char** arr, int size){

	PUSH_TRACE("extend_array");
	char** temp = (char**) realloc(arr, size * sizeof(char*)); //realocates the size to the size of the argument
	POP_TRACE();
	
	return temp;
}

//recursively prints the nodes of the linked list
void PrintNodes(node_t* input){
	//initialize node
	node_t* tempNode = NULL;
	tempNode = input;
	if(tempNode == NULL){ 
	//basecase / terminating case
		return;
	}
	if(tempNode->line != NULL){ 
	//if the node has a line attribute, print out its index and line.
		printf("Index %d: %s\n",tempNode->index, tempNode->line);
	}
	if(tempNode->right != NULL){
	//if there is a next node, recursively call PrintNodes with the next node as an argument
		PrintNodes(tempNode->right);
	}
}

//Frees memory allocated to linked list using while loop
void FreeNodes(node_t* input){
	PUSH_TRACE("deallocate_node_memory");
	node_t* deleteNode = input;
	
	//while a the end of the linked list has not been reached
	while(deleteNode != NULL){
		//hold the address of the next node
		node_t* temp = deleteNode->right;
		if(deleteNode->line != NULL){
			//free the memory held by the line attribute
			free(deleteNode->line);
		}
		//free the node memory itself
		free(deleteNode);
		deleteNode = temp;
	}
	POP_TRACE();
}



int main(int argc, char** argv)
{	
	//open output file
	int outputFile = open("mem_tracer.out", O_RDWR | O_CREAT | O_TRUNC, 0777);
	//make outputFile be the stdout using dup2();
	dup2(outputFile, STDOUT_FILENO);
	
	//initial array size, assumed max string length, current count of the line
	int arrSize = 10;
	int MAX_LINE_SIZE = 100;
	int count = 0;
	
	PUSH_TRACE("main");
	
	//allocate memory for the dynamic arguments array 
	char** args = (char**)malloc(arrSize * sizeof(char*));
	//buffer that will hold inputs
	char* input_buffer = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
	
	POP_TRACE();
	
	//allocate memory for the head node of the linked list and initialize a tracker node "currNode"
	node_t* headNode = NULL;
	node_t* currNode = NULL;

	//while EOF not reached OR CTRL+D not pressed...
	while(fgets(input_buffer, MAX_LINE_SIZE, stdin) != NULL){
		//remove '\n' at end of the string
		input_buffer[strlen(input_buffer) - 1] = '\0';
		//assign the row index of the dynamic args array with the recently read input using strdup()
		args[count] = strdup(input_buffer);

		if(count == 0){
		//if first iteration, set the data of the headNode of the linkedlist
			headNode = (node_t*)malloc(sizeof(node_t));
			//assigns line attribute
			headNode->line = strdup(input_buffer);
			//assigns index attribute
			headNode->index = count;
			//assigns currNode
			currNode = headNode;
		}else{
			PUSH_TRACE("new_node");
			node_t* temp = (node_t*)malloc(sizeof(node_t));
			if(input_buffer != NULL){
				//assigns line attribute and index attribute
				temp->line = strdup(input_buffer);
				temp->index = count;
			}
			//set the next of the temp
			currNode->right = temp;
			currNode = currNode->right;
			POP_TRACE();
		}
		count++;
		
		//if the count in the array is the same size as the array, reallocate memory
		if(count == arrSize){
			arrSize++;
			char** newArgs = extend_array(args, arrSize);
			if(newArgs == NULL){
				free(args);
				return 1;
			}
			args = newArgs;
			
		}
		
	}

	if(headNode != NULL){
		printf("\nPrinting Nodes:\n");
		PrintNodes(headNode);
		FreeNodes(headNode);
	}
	
		
	
	
	PUSH_TRACE("free_memory");
	//free memory
	for(int i = 0; i < count; i++){
		free(args[i]);
	}

	free(args);
	free(input_buffer);
	POP_TRACE();
	
	free(TRACE_TOP);

        
        return(0);
}






