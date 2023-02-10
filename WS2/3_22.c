#include <stdio.h>

int main(void) {
   
   int first;
   int second;
   int third;
   
   scanf("%d", &first);
   scanf("%d", &second);
   scanf("%d", &third);
   
   int smallest = first;

   if(second < smallest){
      smallest = second;  
   }
   if(third < smallest){
      smallest = third;
   }  
   printf("%d\n",smallest);
   return 0;
}

