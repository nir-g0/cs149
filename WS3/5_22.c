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
   
   int lowerBound;
   scanf("\n%d",&lowerBound);
      
   int upperBound;
   scanf("%d",&upperBound);
   
   for(int i = 0; i < length; i++){
      int val = userValues[i];
      if(val >= lowerBound && val <= upperBound){
         printf("%d,", val);
      }
   }
   
   printf("\n");
   
   return 0;
}

