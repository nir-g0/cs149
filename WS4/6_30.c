#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4){
   int max1 = num1 > num2 ? num1 : num2;
   int max2 = num3 > num4 ? num3 : num4;
   
   return max1 > max2 ? max1 : max2;  
}

int MinNumber(int num1, int num2, int num3, int num4){
   int min1 = num1 < num2 ? num1 : num2;
   int min2 = num3 < num4 ? num3 : num4;
   
   return min1 < min2 ? min1 : min2;  
}

int main(void) {

   int num1, num2, num3, num4;
   
   scanf("%d",&num1);
   scanf("%d",&num2);
   scanf("%d",&num3);
   scanf("%d",&num4);
   
   printf("Maximum is %d\n", MaxNumber(num1,num2,num3,num4));
   printf("Minimum is %d\n", MinNumber(num1,num2,num3,num4));
   
   return 0;
}

