/****************************************************************
 * Fecha: 25 - Julio - 2023
 * Autor: Juan Sebastian Clavijo Martinez
 * Tema: modularización
 * Objetivo: programa principal a ser modu
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*Se reserva memoria*/
#define SIZE_DATA (1024*1024*8)

static double MEM_CHUNK[SIZE_DATA];

/* Función para inicialización de las Matrices*/
void init_Matriz(int n, double *a, double *b, double *c){
	int i, j;
	for (i=0; i < n; i++){
		for (j=0; j < n; j++){
			a[j+i*n] = 2.1+i;
			b[j+i*n] = 3.2+i*j;
			c[j+i*n] = 0.0;
		}
	}
}

	/*Visualización de las Matrices*/
void Impr_Matriz(int n, double *a){
	int i, j;
	for (i=0; i < n; i++){
		for (j=0; j < n; j++){
			printf(" %f ", a[j+i*n]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	/* Se condiciona a que los argumentos de entrada sea la cantidad
	 * correcta */
	if (argc < 2){
		printf("Argumentos de entrada: ./ejecutable N \n");
		return -1;
	}

	/*Se quiere que el tamaño de la matriz sea ingresado al llamar al programa*/
	int N = (int) atof(argv[1]);

	/*Se reserva el espacio para las matrices con punteros (enteros)*/
	double *A = MEM_CHUNK;
	double *B = A + N*N;
	double *C = B + N*N;

	init_Matriz(N, A, B, C);

	Impr_Matriz(N, A);
	Impr_Matriz(N, B);

	/*Calculo de multiplicación de matrices:
	 * Se empleará el algoritmo clásico FilasxColumnas 
	 * Se requiere que la manipulación de las matrices sea
	 * por punteros */
	for (int i=0; i < N; i++){
		for (int j=0; j < N; j++){
			/*Punteros auxiliares, variable auxiliar de cálculo*/
			double *pauxA, *pauxB, auxCalculo = 0;
			/*Se apuntan los punteros según el algoritmo*/
			pauxA = A+(N*i); 
			pauxB = B+j; 
			for (int k=0; k < N; k++, pauxA++, pauxB+=N){
				auxCalculo += (*pauxA * *pauxB);	
			}
			C[i*N+j] = auxCalculo;	
		}
	}


	Impr_Matriz(N, C);



	return 0;
}
