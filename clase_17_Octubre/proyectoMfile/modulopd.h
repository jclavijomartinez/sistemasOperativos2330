#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

#ifndef MODULOPD_H_INCLUDE

#define MODULOPD_H_INCLUDE

/***PROTOTIPOS DE FUNCIONES***/

bool divisionhorizontal(int numpor, int nfilas, int numcols, int numprocesos, int ***matriz);
bool divisionvertical(int numpor, int nfilas, int ncols, int numprocesos, int ***matriz);;
bool filasycolsdelarchivo(char *archivo, int filas, int cols);
void printmat(int filas, int cols, int** matrix);
void crearmatriz(int nfil, int ncol, int ***mat);
void cargarmatriz(FILE *arch, char *archivo, int filas, int cols, int **matriz);

#endif

