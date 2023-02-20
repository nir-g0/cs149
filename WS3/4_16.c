#include <stdio.h>

int main(void) {
   double average = 0;
   int count = 0;
   int max = 0;
   while(1){
      int in;
      scanf("%d",&in);
      if(in < 0){
         break;
      }
      if(in > max){
         max = in;
      }
      average += in;
      count += 1;
   }
   average /= count;
   printf("%d ", max);
   printf("%0.2lf\n", average);
   return 0;
}

