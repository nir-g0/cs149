#include <stdlib.h>

int main() {
    int *test = malloc(sizeof(int));
    *test = 10;
    return 0;
}

/*
	When the program runs, the program delegates memory for the test pointer at the size of one integer.
	The program returns without freeing any memory that was allocated.

	gdb does not find problems with it
	
	valgrind returns the following:
	
	==2534== HEAP SUMMARY:
	==2534==     in use at exit: 4 bytes in 1 blocks
	==2534==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
	==2534== 
	==2534== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
	==2534==    at 0x4865058: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
	==2534==    by 0x108763: main (q4.c:4)
	==2534== 
	==2534== LEAK SUMMARY:
	==2534==    definitely lost: 4 bytes in 1 blocks
	==2534==    indirectly lost: 0 bytes in 0 blocks
	==2534==      possibly lost: 0 bytes in 0 blocks
	==2534==    still reachable: 0 bytes in 0 blocks
	==2534==         suppressed: 0 bytes in 0 blocks
	
	essentially writing that 4 bytes of memory are allocated and lost once the program exits

*/
