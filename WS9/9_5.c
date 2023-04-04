#include<stdio.h>
#include <string.h>

int main(void) {

   
   char input[100];
   int comma;
   int index;
   
   while(fgets(input, 100, stdin)){
         printf("Enter input string:\n");
         if(strcmp(input, "q") == 0 || strcmp(input, "q\n") == 0){
            break;
         }
         comma = 0;
         index = 0;
         for(index = 0; index < strlen(input); index++){
            if(input[index] == ','){
                 comma = 1;
                 break;
            }
         }
         if(comma == 0){
            printf("Error: No comma in string.\n");
         }
         else{
            int pos1 = index;
            int pos2 = index+1;
            
            if(input[index-1] ==' '){
                  pos1 -= 1;
            }
            printf("First word: ");
            for(int i = 0; i < pos1; i++){
               printf("%c",input[i]);
            }
            
            if(input[index + 1] == ' '){
               pos2 += 1;  
            }
            printf("\nSecond word: ");
            for(int i = pos2; i < strlen(input); i++){
               printf("%c",input[i]);
            }
         }
         printf("\n");
   }
   

   return 0;
}
