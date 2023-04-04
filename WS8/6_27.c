#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char* userString, char userChar){
   
   int length = strlen(userString);
   int count = 0;
   
   for(int i = 0; i < length; i++){
      if(userString[i] == userChar){
         count++;
      }
   }
   
   return count;
     
}


int main(void) {

   char* userString;
   char userChar;
   
   scanf("%c",&userChar);
   scanf("%s",userString);
   
   int output = CalcNumCharacters(userString, userChar);
   
   if(output == 1){
      printf("1 %c\n", userChar);
   }
   else{
      printf("%d %c's\n", output, userChar);  
   }
   
   return 0;
}

