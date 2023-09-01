/****************************************************************
 * Fecha: 01 - Septiembre - 2023
 * Autores: Juan Sebastian Clavijo Martinez, Jorge Torrado Y Juan Diego Perez
 * Clase: Sistemas Operativos
 * Objetivo: Aplicacion de conceptos y comunicación entre procesos
 ***************************************************************/

//includes respectivos 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//funcion que lee los archivos y carga a los vectores de punteros

void cargarPunteros(FILE *arch , char *archivo ,int *vect){
    arch = fopen(archivo,"r");
    printf("si abre el archivoXD\n");
    fclose(arch);
}

//main en el cual se hace la verificacion de que la info ingresada en el comando sea correcta

int main(int argc, char *argv[]){
    int N1 = (int)atof(argv[1]);
    int N2 = (int)atof(argv[3]);
    char *archivo00 = argv[2];
    char *archivo01 = argv[4];
    int vector0[N1];
    int vector1[N2];
    int *ptrv0 = vector0;
    int *ptrv1 = vector1;
    FILE *arch00;
    FILE *arch01;
    cargarPunteros(arch00,archivo00,ptrv0);
    //printf("la info ingresada es: %d , %s , %d, %s\n",N1,archivo00,N2,archivo01);
    return 0;
}
