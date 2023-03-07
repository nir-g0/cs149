#include <stdio.h>
#include <string.h>

int main() {
    char str[50];
    int count = 0;
    int i = 0;

    fgets(str, 50, stdin);

    while (str[i] != '\0') {
        if (!isspace(str[i]) && str[i] != '.' && str[i] != '!' && str[i] != ',') {
            count++;
        }
        i++;
    }

    printf("%d\n", count);

    return 0;
}
