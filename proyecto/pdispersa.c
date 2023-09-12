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

//funcion que crea (reserva el espacio para las matrices)
int **crearmatriz(int nfil, int ncol, int** mat){
    mat = (int **)malloc(nfil*sizeof(int *));
    if (mat == NULL) {
        perror("Error al asignar memoria para las filas de la matriz");
        free(mat);
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<nfil;i++){
        (mat)[i]=(int *)malloc(ncol*sizeof(int));
    }
    return mat;
}


//funcion que carga la matriz desde el archivo a memoria
void cargarmatriz(FILE *arch, char *archivo,int filas, int cols, int **matriz) {
    arch = fopen(archivo, "r"); //se abre el archivo, como no se tiene que modificar, se usa r
    if (arch == NULL) {
        perror("Error al abrir el archivo"); //si no se puede abrir el archivo, se devuelve un error 
        exit(EXIT_FAILURE);
    }
    //se lleva a memoria la info del archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(arch,"%d",&(matriz[i][j]));
        }
    }
    printf("Los contenidos del archivo, %p, se cargaron exitosamente en memoria\n",archivo);
    fclose(arch);
    printf("El archivo se abrio y cerro exitosamente\n");
}

int main(int argc, char *argv[]){ //argv[0] es el nombre del ejecutable
    //se inicializan las variables para recibir los datos del usr dados en la terminal
    int numfils=-1;
    int numcols=-1;
    char *archivo = NULL;
    FILE *arch;
    int numproc=-1;
    int numpor=-1;
    int opc;
    int **matriz;
    //se verifica que lo que haya pasado por consola del usr si tenga el largo esperado
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
    //se llama la funcion que reserva el espacio de memoria para la matriz
    crearmatriz(numfils,numcols,matriz);
    //se llama a la funcion que carga la matriz en memoria
    cargarmatriz(arch,archivo,numfils,numcols,matriz);
    //se liberan los recursos de memoria usados, empezando por la matriz
    for (int i = 0; i < numcols; i++) {
        free(matriz[i]);
    }
    free(matriz);
    /*
    prints de ayuda para verificar que los datos ingresados sean correcto IGNORAR
    printf("Filas: %d\n", numfils);
    printf("Columnas: %d\n", numcols);
    printf("Archivo: %s\n", archivo);
    printf("N Procesos: %d\n", numproc);
    printf("Porcentaje: %d\n", numpor);
    */
	return 0;
}
