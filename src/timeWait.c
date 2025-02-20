#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_hijo, pid_nieto, pid_bisnieto;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    pid_hijo = fork();
    if (pid_hijo == 0) {  // Proceso hijo
        pid_nieto = fork();
        if (pid_nieto == 0) {  // Proceso nieto
            pid_bisnieto = fork();
            if (pid_bisnieto == 0) {  // Proceso bisnieto
                // El bisnieto realiza un ciclo for de un millón de iteraciones
                for (long i = 0; i < 1000000; i++);
                return 0;  // Termina el bisnieto
            }
            // El nieto espera a que termine el bisnieto antes de continuar
            wait(NULL);
            for (long i = 0; i < 1000000; i++);
            return 0;  // Termina el nieto
        }
        // El hijo espera a que termine el nieto antes de continuar
        wait(NULL);
        for (long i = 0; i < 1000000; i++);
        return 0;  // Termina el hijo
    }

    // El proceso padre espera a que termine el hijo antes de continuar
    wait(NULL);
    
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Tiempo transcurrido (con fork): %f segundos\n", cpu_time_used);

    return 0;
}
