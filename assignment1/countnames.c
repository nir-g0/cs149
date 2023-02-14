#include <stdio.h>

int main(int* argc, char **argv){
	
	FILE *fp;
	fp = fopen(argv[1],"r");
	if(fp == NULL) {
     	  perror("Error opening file");
    	  return(-1);
   	}
   	else{
   	  char g[30];
   	  fgets(g, 30, fp);
   	  printf("%s",g);
   	  fgets(g, 30, fp);
   	  printf("%s",g);
   	}
	
	return 0;
}
