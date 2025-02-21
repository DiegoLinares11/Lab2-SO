#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Proceso hijo
        for (int i = 1; i <= 4000000; i++) {
            printf("%d\n", i);
        }
        return 0;
    } else { // Proceso padre
        printf("Padre (PID: %d). Hijo: %d\n", getpid(), pid);
        while (1) {} // Bucle infinito
    }

    return 0;
}