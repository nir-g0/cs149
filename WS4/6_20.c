#include <stdio.h>

/* Define your function here */ 
double LapsToMiles(double userLaps){
   return userLaps/4;
}

int main(void) {
   
   double userInput;
   
   scanf("%lf", &userInput);
   
   printf("%0.2lf\n", LapsToMiles(userInput));

   return 0;
}
