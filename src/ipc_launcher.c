#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SHM_NAME "/shared_memory"

int main() {
    // Borrar memoria compartida previa (para empezar desde cero)
    shm_unlink(SHM_NAME);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {  
        // Proceso hijo 1 ejecuta ipc con 'b'
        execl("./ipc", "./ipc", "20", "b", (char *)NULL);
        perror("execl");
        return EXIT_FAILURE;
    }

    sleep(1); // Esperar para evitar condiciones de carrera

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {  
        // Proceso hijo 2 ejecuta ipc con 'a'
        execl("./ipc", "./ipc", "20", "a", (char *)NULL);
        perror("execl");
        return EXIT_FAILURE;
    }

    // Esperar que ambos procesos terminen
    wait(NULL);
    wait(NULL);
    shm_unlink(SHM_NAME);

    return EXIT_SUCCESS;
}
