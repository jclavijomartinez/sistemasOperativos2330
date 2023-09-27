/****************************************************************
 * Fecha: 29 - Agosto - 2023
 * Autor: Juan Clavijo
 * Tema: Fuente para generar ficheros con un array de enteros se recibe el nombre del fichero y la conudad de elementos 
 * Objetivo: 
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Argumentos: ./ejecutable nomfichero filas columnas\n");
        return -1;
    }

    char *ficheroa = argv[1]; // Nombre del archivo
    int rows = atoi(argv[2]); // Número de filas
    int cols = atoi(argv[3]); // Número de columnas

    FILE *fileA = fopen(ficheroa, "w"); // Abre el archivo para escritura

    srand(time(NULL)); // Genera la semilla de aleatoriedad

    // Porcentaje de ceros ingresado por el usuario
    int porcentaje = 50; // Por defecto al 50%
    if (argc == 5) {
        porcentaje = atoi(argv[4]);
        if (porcentaje < 0 || porcentaje > 100) {
            printf("El porcentaje debe estar en el rango de 0 a 100.\n");
            return -1;
        }
    }

    int contador1=0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            double valor = (double)rand()/RAND_MAX ; // Genera un valor aleatorio entre 0 y 1
            int total_elem_uno = (porcentaje/100)*rows*cols; 
            int val_fin = (contador1<total_elem_uno) ? 1 : 0;
            if (val_fin ==1){
                contador1++;
            }

            // Imprime el valor en el archivo
            fprintf(fileA, "%d ", val_fin);
        }
        fprintf(fileA, "\n"); // Nueva línea después de cada fila
    }

    fclose(fileA);

    return 0;
}

