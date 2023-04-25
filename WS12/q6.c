#include <stdio.h>
#include <stdlib.h>

int main() {
    int* array = malloc(sizeof(int) * 100);
    free(array);
    printf("%d\n", array[33]);
    return 0;
}

/*

When the target index to print is not 0, the program prints 0, otherwise it prints a random garbage value like: -1431397761

Valgrind output:

==3589== Invalid read of size 4
==3589==    at 0x108838: main (q6.c:7)
==3589==  Address 0x4a4a0c4 is 132 bytes inside a block of size 400 free'd
==3589==    at 0x4867AD0: free (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3589==    by 0x10882F: main (q6.c:6)
==3589==  Block was alloc'd at
==3589==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3589==    by 0x108823: main (q6.c:5)
==3589== 
==3589== 
==3589== HEAP SUMMARY:
==3589==     in use at exit: 0 bytes in 0 blocks
==3589==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated
==3589== 
==3589== All heap blocks were freed -- no leaks are possible


*/
