/****************************************************************
 * Fecha: 10-09-2023
 * Autor: Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co)
 * Tema: proyecto 1
 * Objetivo: 
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>

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
    printf("funciona\n");
	return 0;
}
