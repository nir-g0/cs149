#include <stdlib.h>
#include <stdio.h>

int main() {
    int* array = (int*) malloc(100 * sizeof(int));
    array[100] = 0;
    free(array); // free the memory
    return 0;
}

/*

When I run this program nothing happens, and it simply terminates.

Valgrind writes that all memory is freed, however, we make an invalid write of 4 bytes since the index
100 is considered out of bounds for the memory that we allocated. The program is not correct

/*
