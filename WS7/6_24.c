#include <stdio.h>

void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4){
   int temp = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = temp;
    
   temp = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = temp;
    
   printf("%d %d %d %d\n",*userVal1, *userVal2, *userVal3, *userVal4);
}

int main(void) {
   
   int inputArr[4];
   int input;
   for(int i = 0; i < 4; i++){
      scanf("%d",&input);  
      inputArr[i] = input;
   }
   
   int* userVal1 = &inputArr[0];
   int* userVal2 = &inputArr[1];
   int* userVal3 = &inputArr[2];
   int* userVal4 = &inputArr[3];
   
   SwapValues(userVal1, userVal2, userVal3, userVal4);
   
   
   
   return 0;
}
