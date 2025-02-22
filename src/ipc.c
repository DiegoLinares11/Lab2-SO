#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define SHM_NAME "/shared_memory"
#define MEM_SIZE 256 

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <n> <x>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];
    int shm_fd;
    char *shm_ptr;
    int pipefd[2];

    // Intentar abrir la memoria compartida
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    // Ajustar el tamaño de la memoria compartida
    if (ftruncate(shm_fd, MEM_SIZE) == -1) {
        perror("ftruncate");
        return EXIT_FAILURE;
    }

    // Mapear la memoria compartida
    shm_ptr = mmap(0, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        return EXIT_FAILURE;
    }


    // Crear el pipe para la comunicación padre-hijo
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {  // Proceso hijo
        close(pipefd[1]);  // Cerrar el lado de escritura
        int index = strlen(shm_ptr); // Empezar a escribir desde el final actual
        char received;
        while (read(pipefd[0], &received, 1) > 0 && index < MEM_SIZE - 1) {
            shm_ptr[index++] = received;
        }
        shm_ptr[index] = '\0';  // Finalizar la cadena
        close(pipefd[0]);
    } else {  // Proceso padre
        close(pipefd[0]);  // Cerrar el lado de lectura
        for (int i = 1; i <= MEM_SIZE; i++) {   
            if (i % n == 0) {
                write(pipefd[1], &x, 1);
            }
        }
        close(pipefd[1]);  // Cerrar la escritura
        wait(NULL);  // Esperar al hijo
        printf("Memoria compartida contiene: %s\n", shm_ptr);
    }

    // Limpiar recursos (pero NO borrar la memoria compartida)
    munmap(shm_ptr, MEM_SIZE);
    close(shm_fd);

    return EXIT_SUCCESS;
}
