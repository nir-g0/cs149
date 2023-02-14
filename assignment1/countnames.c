#include <stdio.h>
#include <string.h>

int main(int* argc, char **argv){

	char names[100][30] = {};
	int times[100] = {[0 ... 99] = 0};
	
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

   	  	}
   	  	else{
   	  		for(int i = 0; i < 100; i++){
   	  			if(strcmp(names[i], name) == 0){
   	  				times[i] = times[i]+1;
   	  				break;
   	  			}
   	  			if(strlen(names[i]) == 0){
   	  				for(int b = 0; b < 30; b++){
   	  					names[i][b] = name[b];
   	  				}
   	  				times[i] = 1;
   	  				break;
   	  			} 
   	  		}
   	  	}
   	  	fgets(name, 30, fp);
   	  	complete = feof(fp);
   	  }
   	}
	
	for(int i = 0; i < 100; i++){
		if(strlen(names[i]) != 0){
			printf("%s printed %d", names[i], times[i]);
		}
	}
	
	return 0;
}
