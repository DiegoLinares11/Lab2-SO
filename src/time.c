#include <stdio.h>
#include <time.h>
#include <sys/time.h>  

int main() {
    struct timeval start, end;
    double tiempo_real;

    gettimeofday(&start, NULL);  

    // Tres ciclos for vacíos de un millón de iteraciones cada uno
    for (long i = 0; i < 1000000; i++) {
        printf("Iteracion 1: %ld\n", i);
    }  
    for (long i = 0; i < 1000000; i++) {
        printf("Iteracion 2: %ld\n", i);
    }  
    for (long i = 0; i < 1000000; i++) {
        printf("Iteracion 3: %ld\n", i);
    }  

    gettimeofday(&end, NULL);  

    // Cálculo del tiempo real transcurrido en segundos
    tiempo_real = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Tiempo real (secuencial): %f segundos\n", tiempo_real);

    return 0;
}
