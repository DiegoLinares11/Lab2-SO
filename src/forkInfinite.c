#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Proceso hijo
        printf("Soy el proceso hijo (PID: %d)\n", getpid());
        return 0;
    } else { // Proceso padre
        printf("Soy el proceso padre (PID: %d)\n", getpid());
        while (1) {} // Bucle infinito
    }

    return 0;
}