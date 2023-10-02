/**********************
 * Fecha: 01-10-2023
 * Autores: 
 *  - Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co), 
 *  - Santiago Mesa Niño (santiagoa.mesan@javeriana.edu.co), 
 *  - Juliana Lugo Martínez (julugo@javeriana.edu.co)
 * Titulo: hdispersa.c
 * Tema: Primer Proyecto
 * Objetivo: Determina si una matriz es dispersa, analizando la proporción de elementos diferentes de cero en la matriz. Se divide en funciones que permiten procesar las filas y columnas de la matriz en paralelo utilizando hilos. El programa carga la matriz desde un archivo y permite elegir el número de hilos para el procesamiento en paralelo, así como el umbral que define la dispersión de la matriz.
 *********************/

//includes respectivos
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include "hdispersa.h";

int main(int argc, char *argv[]){
    // Inicializar las variables para recibir los datos del usuario dados en la terminal
    int numfils=-1;
    int numcols=-1;
    char *archivo = NULL;
    FILE *arch;
    int numthreads=-1;
    int numpor=-1;
    int opc;
    int **matriz;

    // Inicializar la librería de hilos
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Verificar que los argumentos pasados por la terminal sean suficientes
    if (argc < 10) {
        printf("No estoy seguro de que los argumentos ingresados sean correctos. REVISA\n\n");
        return -1;
    }

    // Recorrer la llamada desde la terminal para identificar los selectores y almacenar las variables donde correspondan
    while ((opc = getopt(argc, argv, "f:c:a:n:p:")) != -1) {
        switch (opc) {
            case 'f':
                numfils = atoi(optarg); // Obtener el número de filas desde la terminal
                break;
            case 'c':
                numcols = atoi(optarg); // Obtener el número de columnas desde la terminal
                break;
            case 'a':
                archivo = optarg; // Obtener el nombre del archivo desde la terminal
                break;
            case 'n':
                numthreads = atoi(optarg); // Obtener el número de hilos desde la terminal
                break;
            case 'p':
                numpor = atoi(optarg); // Obtener el porcentaje desde la terminal
                break;
            default:
                fprintf(stderr, "Uso: %s -f filas -c columnas -a archivo.txt -n nthreads -p porcentaje\n\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Verificar que las filas y columnas especificadas coincidan con las del archivo
    if (filasycolsdelarchivo(archivo, numfils, numcols)) {
        // Reservar espacio de memoria para la matriz
        crearmatriz(numfils, numcols, &matriz);
        // Cargar los elementos de la matriz desde el archivo a la memoria
        cargarmatriz(arch, archivo, numfils, numcols, &matriz);
        // Imprimir la matriz cargada en la memoria
        printf("La matriz en memoria se ve así: \n\n");
        printmat(numfils, numcols, matriz);
        printf("\n");

        // Verificar si es posible dividir las filas o columnas entre los hilos
        if (numfils % numthreads == 0) {
            // Llamar a la función de división horizontal y determinar si la matriz es dispersa
            if (divisionhorizontal(numpor, numfils, numcols, numthreads, &matriz)) {
                printf("La matriz es dispersa.\n\n"); // Es dispersa
            } else {
                printf("La matriz no es dispersa.\n\n"); // No es dispersa
            }
        } else if (numcols % numthreads == 0) {
            // Llamar a la función de división vertical y determinar si la matriz es dispersa
            if (divisionvertical(numpor, numfils, numcols, numthreads, &matriz)) {
                printf("La matriz es dispersa.\n\n"); // Es dispersa
            } else {
                printf("La matriz no es dispersa.\n\n"); // No es dispersa
            }
        } else {
            // Si no es posible dividir exactamente, decidir basándose en la dimensión más grande
            if (numfils > numcols) {
                if (divisionhorizontal(numpor, numfils, numcols, numthreads, &matriz)) {
                    printf("La matriz es dispersa.\n\n"); // Es dispersa
                } else {
                    printf("La matriz no es dispersa.\n\n"); // No es dispersa
                }
            } else if (numcols > numfils) {
                if (divisionvertical(numpor, numfils, numcols, numthreads, &matriz)) {
                    printf("La matriz es dispersa.\n\n"); // Es dispersa
                } else {
                    printf("La matriz no es dispersa.\n\n"); // No es dispersa
                }
            } else {
                // Si ambas dimensiones son iguales, se puede elegir cualquier método
                if (divisionhorizontal(numpor, numfils, numcols, numthreads, &matriz)) {
                    printf("La matriz es dispersa.\n\n"); // Es dispersa
                } else {
                    printf("La matriz no es dispersa.\n\n"); // No es dispersa
                }
            }
        }
    } else {
        printf("¿Estás seguro de que ingresaste el número de columnas y filas correctamente?\n\n");
        return -1;
    }