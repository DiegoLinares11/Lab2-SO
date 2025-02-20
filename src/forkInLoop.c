#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void forkInLoop()
{
    for (int i = 0; i < 4; i++)
    {
        fork();
    }
}

int main()
{
    forkInLoop();
    printf("Hola desde el proceso del lopp!, PID: %d\n", getpid());
    return 0;
}