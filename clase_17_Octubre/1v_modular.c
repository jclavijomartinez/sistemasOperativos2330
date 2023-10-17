/*******************************************************
*Autor: J.Daniel Vargas Pedraza
*Fecha: 10 octubre 2023
*Objetivo: Programa principal a ser modularizado
 Crear un programa que crea una matriz dinamica, presentada por pantalla
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

//Función reserva el espacio de memoria

size_t **reservaMem(size_t N){
size_t **entregaMM;
entregaMM = (size_t **) calloc(dim, sizeof(size_t));
for(size_t i = 0; i<dim; i++)
matriz[i] = (size_t *) malloc (dim * sizeof(size_t));
return **entregaMM;
}

//Función para la inicialización de la matriz mediante numeros aleatorios en un rango de 1 a 100

size_t **initMM(size_t N){
size_t **MM;
for(size_t i=0; i<dim;++i){
for(size_t j=0; j<dim;++j){
entregaMM[i][j] = (size_t) rand()%100 + 1;
}
}
return MM;
}

//Función para impresión de la matriz dinamica resultante

void imprimirMM(size_t **mm, size_t N){
size_t **entregaMM;
for(size_t i=0; i<dim;++i){
for(size_t j=0; j<dim;++j){
printf("%zu",matriz[i][j]);
}
printf("\n");
}
}

int main(int argc, char *argv[]){
size_t **matriz;
size_t dim =5;
srand(time(NULL));





//Se libera la memoria reservada
for(size_t i=0; i<dim;++i)
free(matriz[i]);
free(matriz);

return 0;
}

