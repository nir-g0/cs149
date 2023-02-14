#include <stdio.h>
#include <string.h>

int main(int* argc, char **argv){

	char names[100][30];
	int times[100];
	
	FILE *fp;
	
	fp = fopen(argv[1],"r");
	
	if(fp == NULL) {
     	  perror("Error opening file");
    	  return(-1);
   	}
   	else{
   	  char name[30];
   	  fgets(name, 30, fp);
   	  int complete = feof(fp);
   	  while(!complete){
   	  	int len = strlen(name);
   	  	if(len == 1){
   	  		printf("\nEmpty Line\n\n");
   	  	}
   	  	else{
   	  	   	printf("%s",name);
   	  	}
   	  	fgets(name, 30, fp);
   	  	complete = feof(fp);
   	  }
   	}
	
	return 0;
}
