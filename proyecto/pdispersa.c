/****************************************************************
 * Fecha: 10-09-2023
 * Autor: Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co)
 * Tema: proyecto 1
 * Objetivo: 
 ***************************************************************/

//includes respectivos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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


//funcion que carga la matriz desde el archivo a memoria
void cargarmatriz(FILE *arch , char *archivo, int filas, int cols){
    arch = fopen(archivo,"r"); //se abre el archivo
}


int main(int argc, char *argv[]){ //argv[0] es el nombre del ejecutable
    //se inicializan las variables para recibir los datos del usr dados en la terminal
    int numfils=-1;
    int numcols=-1;
    char *archivo = NULL;
    FILE arch;
    int numproc=-1;
    int numpor=-1;
    int opc;
    //se verifica que lo que haya pasado por consola el usr si tenga el largo esperado
    if (argc < 10)
    {
        printf("no estoy seguro que lo que hayas ingresado sea correcto, REVISA\n");
        return -1;
    }
    //se recorre la llamada desde terminal, para identificar los selectores y almacenar las varibales donde correspondan
    while ((opc = getopt(argc, argv, "f:c:a:n:p:")) != -1) {
        switch (opc) {
            case 'f':
                numfils = atoi(optarg);
                break;
            case 'c':
                numcols = atoi(optarg);
                break;
            case 'a':
                archivo = optarg;
                break;
            case 'n':
                numproc = atoi(optarg);
                break;
            case 'p':
                numpor = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -f filas -c columnas -a archivo.txt -n nprocesos -p porcentaje\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    //se llama a la funcion que carga la matriz en memoria
    /*
    //prints de ayuda para verificar que los datos ingresados sean correctos
    printf("Filas: %d\n", numfils);
    printf("Columnas: %d\n", numcols);
    printf("Archivo: %s\n", archivo);
    printf("N Procesos: %d\n", numproc);
    printf("Porcentaje: %d\n", numpor);
    */
	return 0;
}
