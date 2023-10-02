/**********************
 * Fecha: 01-10-2023
 * Autores: 
 *  - Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co), 
 *  - Santiago Mesa Niño (santiagoa.mesan@javeriana.edu.co), 
 *  - Juliana Lugo Martínez (julugo@javeriana.edu.co)
 * Titulo: pdispersa.c
 * Tema: Primer Proyecto 
 * Objetivo: Determina si una matriz es dispersa o no, analizando la proporción de elementos diferentes de cero en la matriz utilizando múltiples procesos para mejorar la eficiencia en el cálculo.
 *********************/

#ifndef pdispersa.h
#define pdispersa.h

#include <stdbool.h>

bool divisionhorizontal(int numpor, int nfilas, int numcols, int numprocesos, int ***matriz);
bool divisionvertical(int numpor, int nfilas, int ncols, int numprocesos, int ***matriz);
bool filasycolsdelarchivo(char *archivo, int filas, int cols);
void printmat(int filas, int cols, int** matrix);
void *crearmatriz(int nfil, int ncol, int ***mat);
void cargarmatriz(FILE *arch, char *archivo, int filas, int cols, int ***matriz);

#endif