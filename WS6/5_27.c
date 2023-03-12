#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

int main(void) {
   
   char input[MAX_LENGTH] = {};
   while(1){
      fgets(input, MAX_LENGTH, stdin);
      input[strlen(input)-1] = '\0';
      if(strcmp(input,"d") == 0 || strcmp(input,"done") == 0 ||strcmp(input,"Done") == 0){
        break;
      }
      else{
         // printf("%s --> ", input);
          for(int i = strlen(input)-1; i >= 0; i--){
            printf("%c",input[i]);
          }
          printf("\n");
      }
   }

   return 0;
}
