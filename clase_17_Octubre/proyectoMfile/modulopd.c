/**********************
 * Fecha: 24-10-2023
 * Autores: 
 *  - Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co), 
 *  - Santiago Mesa Niño (santiagoa.mesan@javeriana.edu.co), 
 *  - Juliana Lugo Martínez (julugo@javeriana.edu.co)
 * Tema: proyecto 1
 * Objetivo: archivo módulo contiene todos los cuerpos de funciones de pdispersa
 *********************/


//includes respectivos
#include "modulopd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

struct timespec start_time, end_time;

void start_timer() {
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void end_timer() {
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                          (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Tiempo de ejecución: %f segundos\n", elapsed_time);
}

/**********************
 * Función: divisionhorizontal
 * Descripción: Verifica si una matriz es dispersa en la dirección horizontal, dividiendo el trabajo entre múltiples procesos.
 *              Cada proceso hijo se encarga de contar los elementos distintos de cero en un rango de filas de la matriz.
 *              Luego, el proceso padre recoge los resultados y decide si la matriz es dispersa o no.
 * Parámetros de Entrada:
 *   - numpor: Porcentaje de elementos diferentes de cero requerido para considerar la matriz como no dispersa.
 *   - nfilas: Número de filas de la matriz.
 *   - numcols: Número de columnas de la matriz.
 *   - numprocesos: Número de procesos hijos a crear para realizar el conteo.
 *   - matriz: Puntero a la matriz que se va a analizar.
 * Valor de Salida: true si la matriz es dispersa, false si no lo es.
 **********************/
bool divisionhorizontal(int numpor, int nfilas, int numcols, int numprocesos, int ***matriz) {
    int filasPorProceso = nfilas / numprocesos; // Número de filas por proceso
    int filasRestantes = nfilas % numprocesos; // Filas restantes para el último proceso
    int totalElementosDiferentesDeCero = 0; // Contador de elementos diferentes de cero

    // Ciclo que crea procesos hijos para procesar filas de la matriz
    for (int i = 0; i < numprocesos; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Proceso hijo
            int inicio = i * filasPorProceso; // Fila de inicio para este proceso
            int fin = inicio + filasPorProceso; // Fila de fin para este proceso

            // Se añaden las filas restantes al último proceso
            if (i == numprocesos - 1) {
                fin += filasRestantes;
            }

            int count = 0; // Contador de elementos diferentes de cero
            for (int j = inicio; j < fin; j++) {
                for (int k = 0; k < numcols; k++) {
                    if ((*matriz)[j][k] != 0) {
                        count++;
                    }
                }
            }

            // Se muestra el resultado de este proceso
            printf("El proceso hijo con ID: %d encontró %d elementos distintos de cero entre las filas %d y %d\n", getpid(), count, inicio, fin);
            exit(count); // El proceso hijo termina y devuelve el conteo
        }
    }

    // Proceso padre recoge los resultados de los procesos hijos
    for (int i = 0; i < numprocesos; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            totalElementosDiferentesDeCero += WEXITSTATUS(status);
        }
    }

    // Calcula el porcentaje de elementos diferentes de cero en la matriz como un entero
    int total = nfilas * numcols;
    int totalceros = round(total * (numpor / 100.0)); // Asegura que la división sea en punto flotante
    int totalNoCerosPermitidos = total - totalceros;

    printf("El número de ceros debe ser %d\n", totalceros);
    printf("El número de elementos diferentes de cero debe ser %d\n", totalNoCerosPermitidos);

    // Decide si la matriz es dispersa o no
    if (totalceros == 0 || totalceros <= round(total * (10 / 100.0))) {
        return false;
    }

    return totalElementosDiferentesDeCero <= totalNoCerosPermitidos;
}


/**********************
 * Función: divisionvertical
 * Descripción: Verifica si una matriz es dispersa en la dirección vertical, dividiendo el trabajo entre múltiples procesos.
 *              Cada proceso hijo se encarga de contar los elementos distintos de cero en un rango de columnas de la matriz.
 *              Luego, el proceso padre recoge los resultados y decide si la matriz es dispersa o no.
 * Parámetros de Entrada:
 *   - numpor: Porcentaje de elementos diferentes de cero requerido para considerar la matriz como no dispersa.
 *   - nfilas: Número de filas de la matriz.
 *   - ncols: Número de columnas de la matriz.
 *   - numprocesos: Número de procesos hijos a crear para realizar el conteo.
 *   - matriz: Puntero a la matriz que se va a analizar.
 * Valor de Salida: true si la matriz es dispersa, false si no lo es.
 **********************/
bool divisionvertical(int numpor, int nfilas, int ncols, int numprocesos, int ***matriz) {
    int colsPorProceso = ncols / numprocesos; // Número de columnas por proceso
    int colsRestantes = ncols % numprocesos; // Columnas restantes para el último proceso
    int totalElementosDiferentesDeCero = 0; // Contador de elementos diferentes de cero

    // Ciclo que crea procesos hijos para procesar columnas de la matriz
    for (int i = 0; i < numprocesos; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Proceso hijo
            int inicio = i * colsPorProceso; // Columna de inicio para este proceso
            int fin = inicio + colsPorProceso; // Columna de fin para este proceso

            // Se añaden las columnas restantes al último proceso
            if (i == numprocesos - 1) {
                fin += colsRestantes;
            }

            int count = 0; // Contador de elementos diferentes de cero
            for (int j = inicio; j < fin; j++) {
                for (int k = 0; k < nfilas; k++) {
                    if ((*matriz)[k][j] != 0) {
                        count++;
                    }
                }
            }

            // Se muestra el resultado de este proceso
            printf("El proceso hijo con ID: %d encontró %d elementos distintos de cero entre las columnas %d y %d\n", getpid(), count, inicio, fin);
            exit(count); // El proceso hijo termina y devuelve el conteo
        }
    }

    // Proceso padre recoge los resultados de los procesos hijos
    for (int i = 0; i < numprocesos; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            totalElementosDiferentesDeCero += WEXITSTATUS(status);
        }
    }

    // Calcula el porcentaje de elementos diferentes de cero en la matriz como un entero
    int total = ncols * nfilas;
    int totalceros = round(total * (numpor / 100.0)); // Asegura que la división sea en punto flotante
    int totalNoCerosPermitidos = total - totalceros;

    printf("El número de ceros debe ser %d\n", totalceros);
    printf("El número de elementos diferentes de cero debe ser %d\n", totalNoCerosPermitidos);

    // Decide si la matriz es dispersa o no
    if (totalceros == 0 || totalceros <= round(total * (10 / 100.0))) {
        return false;
    }

    return totalElementosDiferentesDeCero <= totalNoCerosPermitidos;
}


/**********************
 * Función: filasycolsdelarchivo
 * Descripción: Esta función verifica si las dimensiones de una matriz en un archivo coinciden con las proporcionadas.
 * Parámetros de Entrada:
 *   - archivo: Nombre del archivo que contiene la matriz.
 *   - filas: Número de filas esperado de la matriz.
 *   - cols: Número de columnas esperado de la matriz.
 * Valor de Salida: true si las dimensiones coinciden, false en caso contrario o si hay un error en la lectura del archivo.
 **********************/

bool filasycolsdelarchivo(char *archivo, int filas, int cols) {
    // Se intenta abrir el archivo en modo lectura
    FILE *file = fopen(archivo, "r");

    if (file == NULL) {
        // Si hay un error al abrir el archivo, muestra un mensaje de error y devuelve false
        perror("Error al abrir el archivo");
        return false;
    }

    int num_filas_arch = 0;
    int num_columnas_arch = 0;
    int elementos_primera_linea = 0;
    char linea[51200];

    // Se lee la primera línea del archivo para obtener el número de columnas
    if (fgets(linea, sizeof(linea), file) != NULL) {
        char *token = strtok(linea, " "); // Separa por espacios o tabulaciones
        while (token != NULL) {
            elementos_primera_linea++;
            token = strtok(NULL, " ");
        }
        elementos_primera_linea -= 1; // Se resta 1 para ajustar el conteo
        num_columnas_arch = elementos_primera_linea;
    }

    // Se cuenta el número de filas en el archivo
    while (fgets(linea, sizeof(linea), file)) {
        num_filas_arch++;
    }

    num_filas_arch++; // Se suma 1 para ajustar el conteo
    fclose(file); // Se cierra el archivo

    printf("Número de filas en el archivo: %d\n", num_filas_arch);
    printf("Número de columnas en el archivo: %d\n", num_columnas_arch);

    // Se verifica si las filas y columnas del archivo coinciden con las proporcionadas por el usuario
    if (filas == num_filas_arch && cols == num_columnas_arch) {
        return true; // Si coinciden, devuelve true
    } else {
        return false; // Si no coinciden, devuelve false
    }
}


/**********************
 * Función: printmat
 * Descripción: Esta función imprime una matriz de enteros en la consola.
 * Parámetros de Entrada:
 *   - filas: Número de filas de la matriz.
 *   - cols: Número de columnas de la matriz.
 *   - matrix: Puntero a la matriz de enteros.
 * Valor de Salida: No tiene valor de salida explícito, pero imprime la matriz en la consola.
 **********************/
void printmat(int filas, int cols, int** matrix) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            // Imprime el valor en la posición (i, j) de la matriz, seguido de un espacio
            printf("%d ", matrix[i][j]);
        }
        // Imprime un salto de línea al final de cada fila
        printf("\n");
    }
}


/**********************
 * Función: crearmatriz
 * Descripción: Esta función reserva memoria para una matriz de enteros de tamaño especificado.
 * Parámetros de Entrada:
 *   - nfil: Número de filas de la matriz.
 *   - ncol: Número de columnas de la matriz.
 *   - mat: Puntero a un puntero de punteros que contendrá la matriz.
 * Valor de Salida: No tiene valor de salida explícito, pero asigna memoria para la matriz.
 **********************/
void crearmatriz(int nfil, int ncol, int ***mat){
    // Se reserva espacio en memoria para las filas de la matriz
    *mat = (int **)malloc(nfil * sizeof(int*));
    if (*mat == NULL)
    {
        // Si no se puede reservar memoria para las filas, muestra un mensaje de error y termina el programa.
        printf("ERROR: No se ha podido reservar memoria para la matriz!\n");
        exit(1);
    }

    for (int i = 0; i < nfil; i++)
    {
        // Se reserva espacio en memoria para las columnas de cada fila
        (*mat)[i] = (int *)malloc(ncol * sizeof(int));
        if ((*mat)[i] == NULL) {
            // Si no se puede reservar memoria para las columnas, muestra un mensaje de error y termina el programa.
            printf("ERROR: No se ha podido reservar memoria para las columnas!\n");
            exit(1);
        }
    }
    printf("se ha reservado la memoria para la matriz con éxito!\n");
}


/**********************
 * Función: cargarmatriz
 * Descripción: Esta función carga una matriz de enteros desde un archivo en memoria.
 * Parámetros de Entrada:
 *   - arch: Puntero al archivo abierto para lectura.
 *   - archivo: Nombre del archivo que contiene la matriz.
 *   - filas: Número de filas de la matriz.
 *   - cols: Número de columnas de la matriz.
 *   - matriz: Puntero a la matriz de enteros donde se almacenarán los datos.
 * Valor de Salida: No tiene valor de salida explícito, pero llena la matriz con los datos del archivo.
 **********************/
void cargarmatriz(FILE *arch, char *archivo, int filas, int cols, int **matriz) {
    // Se intenta abrir el archivo en modo lectura
    arch = fopen(archivo, "r");
    if (arch == NULL) {
        // Si hay un error al abrir el archivo, se muestra un mensaje y se termina el programa
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char *linea = NULL; // Puntero para almacenar cada línea del archivo
    size_t longitud = 0; // Longitud de la línea
    ssize_t leidos; // Número de caracteres leídos

    // Se recorre cada fila del archivo
    for (int i = 0; i < filas; i++) {
        // Se lee una línea del archivo
        leidos = getline(&linea, &longitud, arch);
        if (leidos == -1) {
            // Si hay un error al leer la línea, se muestra un mensaje y se termina el programa
            perror("Error al leer desde el archivo");
            free(linea); // Se libera la memoria de la línea
            fclose(arch); // Se cierra el archivo
            exit(EXIT_FAILURE);
        }
        
        // Se divide la línea en tokens basados en espacios para obtener cada valor de la matriz
        char *token = strtok(linea, " ");
        for (int j = 0; j < cols && token != NULL; j++) {
            int valor;
            // Se intenta convertir el token a un entero
            if (sscanf(token, "%d", &valor) == 1) {
                // Si la conversión es exitosa, se asigna el valor a la matriz
                matriz[i][j] = valor;
            } else {
                // Si hay un error en la conversión, se muestra un mensaje y se termina el programa
                perror("Error al convertir token a entero");
                free(linea); // Se libera la memoria de la línea
                fclose(arch); // Se cierra el archivo
                exit(EXIT_FAILURE);
            }
            // Se obtiene el siguiente token de la línea
            token = strtok(NULL, " ");
        }
    }
    // Se libera la memoria de la línea
    free(linea);
    printf("Los contenidos del archivo se cargaron exitosamente en memoria\n");
    // Se cierra el archivo
    fclose(arch);
    printf("El archivo se abrió y cerró exitosamente\n");
}
