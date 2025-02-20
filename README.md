# Laboratorio 2 - Sistemas Operativos

Este proyecto contiene dos programas en C que demuestran el uso de llamadas al sistema `fork()` y `execl()` para la creación y manejo de procesos.

## Funcion open
Int Open (const char *pathname, int flags);

## Funcion read
ssize_t read (int fd, void *buf, size_t count);

## 🚀 Compilación

Para compilar los programas, asegúrate de estar en el mismo directorio que los archivos `forks.c` y `forksInLopp.c`. Luego ejecuta estos comandos en la terminal:

```bash
gcc -o forkInLoop forkInLoop.c && ./forkInLoop
gcc -o forks forks.c && ./forks
```

