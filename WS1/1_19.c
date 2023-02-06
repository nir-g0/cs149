#include <stdio.h>

int main(void) {
   int userNum;
   int secondNum;
   
   printf("Enter integer:\n");
   scanf("%d", &userNum);
   printf("You entered: %d\n", userNum);
   printf("%d squared is %d\n", userNum, userNum*userNum);
   printf("And %d cubed is %d!!\n", userNum, userNum*userNum*userNum);
   
   printf("Enter another integer:\n");
   scanf("%d", &secondNum);
   printf("%d + %d is %d\n", userNum, secondNum, userNum + secondNum);
   printf("%d * %d is %d\n", userNum, secondNum, userNum * secondNum);

   return 0;
}
