#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){

	char names[100][30] = {};
	int times[100] = {[0 ... 99] = 0};
	
	FILE *fp;
	
	fp = fopen(argv[1],"r");
	
	//Checks for error in opening file
	if(fp == NULL) {
     	  perror("Error opening file");
    	  return(-1);
   	}
   	//Iterates through the list of names
   	else{
   	  char name[30];
   	  fgets(name, 30, fp);
   	  int complete = feof(fp);
   	  int line = 1;
   	  //Iterates until reached end of file
   	  while(!complete){
   	  	int len = strlen(name);
   	  	//empty line catch
   	  	if(len == 1){
			fprintf( stderr, "Warning - Line %d is empty\n", line);
   	  	}
   	  	//search name function
   	  	else{
   	  		for(int i = 0; i < 100; i++){ 
   	  			/*if the name is in the list of names, add one to the amount of 		
   	  			times it appears*/
   	  			if(strcmp(names[i], name) == 0){
   	  				times[i] = times[i]+1;
   	  				break;
   	  			}
   	  			//if the name is not in the list of names, add name to the list
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
   	  	line += 1;
   	  }
   	}
	//this loop prints the names and how many times they appear
	for(int i = 0; i < 100; i++){
		if(strlen(names[i]) != 0){
		        names[i][strlen(names[i])-1] = '\0';
			printf("%s: %d\n", names[i], times[i]);
		}
	}
	
	return 0;
}
