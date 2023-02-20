#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   
   int index = 0;
   while(1){
      int in;
      scanf("%d",&in);
      if(in < 0){
         break;
      }
      userValues[index] = in;
      index += 1;
   }
   
   if(index > 9){
      printf("Too many numbers\n");
   }
   else{
      printf("Middle item: %d\n", userValues[(index/2)]);
   }

   return 0;
}

