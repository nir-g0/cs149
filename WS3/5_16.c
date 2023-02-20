#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers
   int input;
   int index = 0;
   while(scanf("%d",&input) != EOF){
      userVals[index] = input;
      index += 1;
   }
   
   for(int i = index - 1; i > 0; i--){
      printf("%d,", userVals[i]);
   }
   printf("\n");
   return 0;
}

