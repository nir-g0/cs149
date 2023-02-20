#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   
   int length;
   scanf("%d",&length);
   
   int in;
   for(int i = 0; i < length; i++){
      scanf("%d",&in);
      userValues[i] = in;
   }
   
   int lessThan;
   scanf("%d",&lessThan);
   
   for(int i = 0; i < length; i++){
      if(userValues[i] <= lessThan){
         printf("%d,", userValues[i]);
      }
   }
   
   printf("\n");

   return 0;
}

