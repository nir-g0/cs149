#include <stdio.h>
#include <string.h>

int main() {
    char string[50];
    int count = 0;
    int i = 0;

    fgets(string, 50, stdin);

    while (string[i] != '\0') {
        if (!isspace(string[i]) && string[i] != '.' && string[i] != '!' && string[i] != ',') {
            count++;
        }
        i++;
    }

    printf("%d\n", count);

    return 0;
}
