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

//includes respectivos
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#Include "pdispersa.h";

int main(int argc, char *argv[]){
    // Se inicializan las variables para recibir los datos del usuario dados en la terminal.
    int numfils=-1;
    int numcols=-1;
    char *archivo = NULL;
    FILE *arch;
    int numproc=-1;
    int numpor=-1;
    int opc;
    int **matriz;
    long num_procesadores = sysconf(_SC_NPROCESSORS_ONLN); // Obtiene el número de procesadores disponibles.

    // Se verifica que el número de argumentos pasados por consola sea el esperado.
    if (argc < 10)
    {
        printf("no estoy seguro que lo que hayas ingresado sea correcto, REVISA\n\n");
        return -1;
    }

    // Se recorre la llamada desde terminal para identificar los selectores y almacenar las variables donde correspondan.
    while ((opc = getopt(argc, argv, "f:c:a:n:p:")) != -1) {
        switch (opc) {
            case 'f':
                numfils = atoi(optarg); // Convierte el argumento a entero y lo asigna a numfils.
                break;
            case 'c':
                numcols = atoi(optarg); // Convierte el argumento a entero y lo asigna a numcols.
                break;
            case 'a':
                archivo = optarg; // Asigna el nombre del archivo.
                break;
            case 'n':
                numproc = atoi(optarg); // Convierte el argumento a entero y lo asigna a numproc.
                break;
            case 'p':
                numpor = atoi(optarg); // Convierte el argumento a entero y lo asigna a numpor.
                break;
            default:
                fprintf(stderr, "Uso: %s -f filas -c columnas -a archivo.txt -n nprocesos -p porcentaje\n\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Se verifica que el número de procesos sea par.
    if (numproc%2!=0){
        printf("recuerda que necesito que el numero de procesos sea PAR revisa!\n\n");
        return -1;
    }

    // Se verifica que las filas y columnas proporcionadas por el usuario coincidan con las del archivo.
    if(filasycolsdelarchivo(archivo,numfils,numcols)){
        // Se reserva espacio en memoria para la matriz.
        crearmatriz(numfils,numcols,&matriz);
        // Se carga la matriz con los datos del archivo.
        cargarmatriz(arch,archivo,numfils,numcols,&matriz);
        // Se imprime la matriz.
        printf("La matriz en memoria se ve asi: \n\n");
        printmat(numfils,numcols,matriz);
        printf("\n");

        // Se verifica que el número de procesadores sea suficiente.
        if (num_procesadores < 1) {
            perror("Error al obtener el número de procesadores");
            return 1;
        } else if (numproc > num_procesadores){
            printf("no es posible ejecutar el programa ya que se piden %d procesos y el computador tiene %ld nucleos, me pides mas procesos que nucleos\n\n",numproc,num_procesadores);
            return -1;
        }

        // Se divide la matriz en grupos y se verifica si es dispersa (sparse).
        if (numfils%numproc==0) {
            if (divisionhorizontal(numpor, numfils, numcols, numproc, &matriz)){
                printf("La matriz es dispersa.\n\n");
            } else {
                printf("La matriz no es dispersa.\n\n");
            }
        } else if (numcols%numproc==0) {
            if (divisionvertical(numpor, numfils, numcols, numproc, &matriz)){
                printf("La matriz es dispersa.\n\n");
            } else {
                printf("La matriz no es dispersa.\n\n");
            }
        } else {
            if (numfils > numcols){
                if (divisionhorizontal(numpor, numfils, numcols, numproc, &matriz)){
                    printf("La matriz es dispersa.\n\n");
                } else {
                    printf("La matriz no es dispersa.\n\n");
                }
            }else if (numcols > numfils){
                if (divisionvertical(numpor, numfils, numcols, numproc, &matriz)){
                    printf("La matriz es dispersa.\n\n");
                } else {
                    printf("La matriz no es dispersa.\n\n");
                }
            }else{
                if (divisionhorizontal(numpor, numfils, numcols, numproc, &matriz)){
                    printf("La matriz es dispersa.\n\n");
                } else {
                    printf("La matriz no es dispersa.\n\n");
                }
            }
        }
    } else {
        printf("estas seguro de que pusiste el numero de columnas y filas correcto?\n\n");
        return -1;
    }