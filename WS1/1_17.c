#include <stdio.h>

int main(void) {
   int baseInt;
   int headInt;
   
   scanf("%d", &baseInt);
   scanf("%d", &headInt);

   printf("    %d\n", headInt);
   printf("    %d%d\n", headInt, headInt);
   
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d\n",headInt,headInt,headInt);
   
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d%d\n",headInt,headInt,headInt,headInt);
   
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d\n",headInt,headInt,headInt);
   
   printf("    %d%d\n", headInt, headInt);
   printf("    %d\n", headInt);

   
   
   
   

   return 0;
}

