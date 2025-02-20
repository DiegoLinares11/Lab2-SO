#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>  // Para gettimeofday()

int main() {
    pid_t pid_hijo, pid_nieto, pid_bisnieto;
    struct timeval start, end;
    double tiempo_real;

    gettimeofday(&start, NULL);  // Medición de tiempo real (no CPU time)

    pid_hijo = fork();
    if (pid_hijo == 0) {  // Proceso hijo
        pid_nieto = fork();
        if (pid_nieto == 0) {  // Proceso nieto
            pid_bisnieto = fork();
            if (pid_bisnieto == 0) {  // Proceso bisnieto
                for (long i = 0; i < 1000000; i++){
                    printf("Iteracion, bisnieto: %ld\n", i);
                }  
                _exit(0);  // Usar _exit() en hijos
            }
            wait(NULL);
            for (long i = 0; i < 1000000; i++){
                printf("Iteracion, nieto: %ld\n", i);
            }  
            _exit(0);
        }
        wait(NULL);
        for (long i = 0; i < 1000000; i++){
            printf("Iteracion, hijo: %ld\n", i);
        }  
        _exit(0);
    }

    wait(NULL);
    gettimeofday(&end, NULL);  // Fin de medición

    // Cálculo del tiempo real transcurrido en segundos
    tiempo_real = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Tiempo real (con fork): %f segundos\n", tiempo_real);

    return 0;
}