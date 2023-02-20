#include <stdio.h>
#include <string.h>

int main(void) {
   
   char wordList[20][10] = {};
   
   int length;
   scanf("%d",&length);
   
   char in[10];
   for(int i = 0; i < length; i++){
      scanf("%s",in);
      for(int b = 0; b < strlen(in); b++){
            wordList[i][b] = in[b];
      }
   }
   
   char c[1];
   scanf("%s", &c);
   
   for(int i = 0; i < length; i++){
      if(strstr(wordList[i], c)){
         printf("%s,", wordList[i]);
      }
   }
   
   printf("\n");
   

   return 0;
}

