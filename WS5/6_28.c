#include <stdio.h>
#include <string.h>

void RemoveNonAlpha(char string[], char stringAlpha[]) {
    int length = strlen(string);
    int j = 0;
    int i = 0;
    for (i = 0; i < length; i++) {
        if (isalpha(string[i])) {
            stringAlpha[j] = string[i];
            j++; //moves the string cursor to the next index
        }
    }

    stringAlpha[j] = '\0'; // Add null terminator to end of output string
}


int main() {
    char userString[51]; 
    char stringAlpha[51];

    fgets(userString, 51, stdin);

    RemoveNonAlpha(userString, stringAlpha);

    printf("%s\n", stringAlpha);

    return 0;
}


