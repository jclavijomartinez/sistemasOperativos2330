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

void cargarPunteros(FILE *arch , char *archivo ,int *vect, int tam){
    char contenido;
    char *buffer = (char*)malloc(tam);
    arch = fopen(archivo,"r"); //se abre el archivo 
    int i = 0;
    //se lee el archivo
    while (fgets(buffer, sizeof(buffer), arch) != NULL) {
        char *token = strtok(buffer, " ");
        while (token != NULL) {
            vect[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");
        }
    }
    for(i = 0; i < tam; i++)
    {
        printf("\nValor %d del arreglo: %d\n", i+1, vect[i]);
    }
    fclose(arch);
    printf("\nLos resultados de %s, fueron alamcenados en memoria\n",archivo);
}

//main en el cual se hace la verificacion de que la info ingresada en el comando sea correcta y despues se ejecutan instrucciones

int main(int argc, char *argv[]){
    if (argc<5){
        printf("\nSeguro que ingresaste por consola los datos bien?\n");
        printf("Recuerda que la estructura del comando debe ser:\n");
        printf("./taller_procesos N1 archivo00.txt N2 archivo01.txt\n");
        printf("DONDE:\n");
        printf("N1 es el numero de elementos que tiene archivo00.txt NO SE TE OLVIDE EL .txt\n");
        printf("archivo00.txt es uno de los 2 archivos que contiene datos\n");
        printf("N2 es el numero de elementos que tiene archivo01.txt\n");
        printf("archivo01.txt es el otro de los 2 archivos que contiene datos NO SE TE OLVIDE EL .txt\n");
        return -1;
    }
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
    cargarPunteros(arch00,archivo00,ptrv0,N1);
    //cargarPunteros(arch01,archivo01,ptrv1);
    //printf("la info ingresada es: %d , %s , %d, %s\n",N1,archivo00,N2,archivo01);
    return 0;
}
