#include <stdio.h>

int main(void) {

   int length;
   scanf("%d\n",&length);
   
   int smallest;
   scanf("%d",&smallest);
   int secondSmallest;
   scanf("%d",&secondSmallest);
   
   if(secondSmallest < smallest){
      int temp = smallest;
      smallest = secondSmallest;
      secondSmallest = temp;
   }
   
   int in;
   for(int i = 0; i < length-2; i++){
      scanf("%d",&in);
      if(in < smallest){
         int temp = smallest;
         smallest = in;
         secondSmallest = temp;
      }
      else if(in < secondSmallest){
         secondSmallest = in;
      }
   }
   
   printf("%d and %d\n", smallest, secondSmallest);
 

   return 0;
}

