#include <stdio.h>

int main(int* argc, char **argv){
	char names[100][30];
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
   	  	printf("%s",name);
   	  	fgets(name, 30, fp);
   	  	complete = feof(fp);
   	  }
   	}
	
	return 0;
}
