#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#ifndef MODULOPD_H_INCLUDE

#define MODULOPD_H_INCLUDE

/***PROTOTIPOS DE FUNCIONES***/

bool divisionhorizontal(int numpor, int nfilas, int numcols, int numprocesos, int ***matriz);

void *threadFuncHorizontal(void *arg);
void *threadFuncVertical(void *arg);
bool divisionhorizontal(int numpor, int nfilas, int numcols, int numthreads, int ***matriz);
bool divisionvertical(int numpor, int nfilas, int ncols, int numthreads, int ***matriz);
bool filasycolsdelarchivo(char *archivo, int filas, int cols);
void printmat(int filas, int cols, int** matrix);
void **crearmatriz(int nfil, int ncol, int*** mat);
void cargarmatriz(FILE *arch, char *archivo, int filas, int cols, int ***matriz);


#endif