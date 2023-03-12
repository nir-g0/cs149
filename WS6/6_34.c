#include <stdio.h>
#include <stdbool.h>

bool IsArrayMult10(int inputVals[], int numVals){
   for(int i = 0; i < numVals; i++){
      if(inputVals[i] % 10 != 0){
         return false;
      }
   }
   return true;
}

bool IsArrayNoMult10(int inputVals[], int numVals){
   for(int i = 0; i < numVals; i++){
      if(inputVals[i] % 10 == 0){
         return false;
      }
   }
   return true;
}


int main(void) {
   int size;
   scanf("%d",&size);
   int values[size];
   for(int i = 0; i<size; i++){
      scanf("%d",&values[i]); 
   }
   
   bool isMult = IsArrayMult10(values, size);
   bool isNotMult = IsArrayNoMult10(values, size);
   
   if(isMult && !isNotMult){
      printf("all multiples of 10\n");
   }
   else if(!isMult && isNotMult){
      printf("no multiples of 10\n");
   }
   else{
      printf("mixed values\n");
   }

   return 0;
}

