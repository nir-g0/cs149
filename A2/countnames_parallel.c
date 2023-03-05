/**
 * Description: This program scans a text file for names and prints the amount of times they appear
 * Author name: Nir Guberman 
 * Author email: Nir.guberman@sjsu.edu
 * Last modified date: 2/20/23
 * Creation date: 2/12/23
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){

	char names[100][30] = {};
	char tempNamesArr[100][30] = {};
	int times[100] = {[0 ... 99] = 0};
	int tempTimesArr[100] = {[0 ... 99] = 0};
	pid_t pid;
	int argNum = 1;
	FILE *fp;
	int namePipe[2];
	int countPipe[2];
	
	if(pipe(namePipe) == -1){
		fprintf(stderr, "Pipe failed");
       		return 1;
	}
	if(pipe(countPipe) == -1){
		fprintf(stderr, "Pipe failed");
        	return 1;
	}
	
	for(int i = 1; i < argc; i++){
	   pid = fork();
	   argNum = i;
	   if(pid == 0){
	   	break;
	   }
	}
	
	if(pid == 0){
	   	//Allow the child process to handle reading the files
		fp = fopen(argv[argNum],"r");
		close(namePipe[0]);
		close(countPipe[0]);
		
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
	   	  	//empty line catch
	   	  	if(name[0]== '\n'){
				fprintf(stderr, "Warning - File %s Line %d is empty\n", argv[argNum], line);
	   	  	}
	   	  	//search name function
	   	  	else{
	   	  		if (name[strlen(name)-1] == '\n'){
	   	  			name[strlen(name)-1] = '\0';
	   	  		}
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
	   	if(write(namePipe[1], names, sizeof(names)) < 0 ){
	   		printf("Error Writing Names Arr\n");
	   	}
	   	if(write(countPipe[1], times, sizeof(times)) < 0){
	   		printf("Error Writing Counts Arr\n");
	   	}
	   	  				
	   	close(countPipe[1]);
	   	close(namePipe[1]);
	   	fclose(fp);
	   	exit(0);
	   }
	
	
	if(pid > 0){
		while(wait(NULL) > 0){
			close(countPipe[1]);
		   	close(namePipe[1]);

			read(namePipe[0],tempNamesArr,sizeof(names));
			read(countPipe[0],tempTimesArr,sizeof(times));
			//this loop reads the names and how many times they appear
			for(int i = 0; i < 100; i++){
				if(strlen(tempNamesArr[i]) != 0){ //read all of the names in the tempArr
					for(int b = 0; b < 100; b++){ 
			  			/*if the name is in the list of names, add one to the amount of 		
			  			times it appears*/
			  			if(strcmp(names[b], tempNamesArr[i]) == 0){
			  				times[i] += tempTimesArr[i];
			  				break;
			  			}
			  			//if the name is not in the list of names, add name to the list
			  			if(strlen(names[b]) == 0){
			  				for(int n = 0; n < 30; n++){
			  					names[b][n] = tempNamesArr[i][n];
			  				}
			  				times[b] = tempTimesArr[i];
			  				break;
			  			} 
		   	  		}
	   	  		}
	   	  		else{
	   	  			break;
	   	  		}
			}
		}
		for(int i = 0; i < 100; i++){
		if(strlen(names[i]) != 0){
		        //names[i][strlen(names[i])-1] = '\0';
			printf("%s: %d\n", names[i], times[i]);
		}
	}
	}
	
	
	return 0;
}
