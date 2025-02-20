#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void forks()
{
    fork();
    fork();
    fork();
    fork();
}

int main()
{
    forks();
    printf("Hola desde el proceso del fork normal, PID: %d\n", getpid());
    return 0;
}
