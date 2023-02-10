#include <stdio.h>

int main(void) {

   int userNum;
   int x;
   scanf("%d", &userNum);
   scanf("%d", &x);
   
   userNum /= x;
   printf("%d ", userNum);
   userNum /= x;
   printf("%d ", userNum);
   userNum /= x;
   printf("%d\n", userNum);

   
   return 0;
}

