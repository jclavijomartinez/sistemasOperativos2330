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

#ifndef hdispersa.h
#define hdispersa.h

#include <stdbool.h>

typedef struct {
    int inicio;
    int fin;
    int numcols;
    int **matriz;
} ThreadData;

void *threadFuncHorizontal(void *arg);
void *threadFuncVertical(void *arg);
bool divisionhorizontal(int numpor, int nfilas, int numcols, int numthreads, int ***matriz);
bool divisionvertical(int numpor, int nfilas, int ncols, int numthreads, int ***matriz);
bool filasycolsdelarchivo(char *archivo, int filas, int cols);
void printmat(int filas, int cols, int **matrix);
void *crearmatriz(int nfil, int ncol, int ***mat);
void cargarmatriz(char *archivo, int filas, int cols, int **matriz);

#endif
