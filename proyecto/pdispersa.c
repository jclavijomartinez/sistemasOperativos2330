/****************************************************************
 * Fecha: 10-09-2023
 * Autor: Juan Sebastian Clavijo Martinez (jsebastian.clavijoc@javeriana.edu.co)
 * Tema: proyecto 1
 * Objetivo: 
 ***************************************************************/

//includes respectivos
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

/*
- matriz
- numfilas
- numproc
*/
int divisionhorizontal(int nfilas, int numprocesos, int ***matriz){ //se basa en el numero de filas
    int elem_diff_cero =0;
    return elem_diff_cero;
}

int divisionvertical(int nfilas, int numprocesos, int ***matriz){ //se basa en el numero de columnas
    int elem_diff_cero =0;
    return elem_diff_cero;
}

int divisionirregular(int nfilas, int numprocesos, int ***matriz){ //se basa en el numero de columnas
    int elem_diff_cero =0;
    return elem_diff_cero;
}

bool filasycolsdelarchivo(char *archivo, int filas, int cols) {
    FILE *file = fopen(archivo, "r");

    if (file == NULL) {
        perror("Error al abrir el archivo");
        return false;
    }

    int num_filas_arch = 0;
    int num_columnas_arch = 0;
    int elementos_primera_linea = 0;
    char linea[1024];
    if(fgets(linea, sizeof(linea), file) != NULL){
        char *token = strtok(linea, " "); // Separa por espacios o tabulaciones
        while (token != NULL) {
            elementos_primera_linea++;
            token = strtok(NULL, " ");
        }
        elementos_primera_linea-=1;
        num_columnas_arch=elementos_primera_linea;
    }

    while (fgets(linea, sizeof(linea), file)) {
        num_filas_arch++;
        char *token = strtok(linea, " \t"); // Dividir la línea en tokens basados en espacios o tabulaciones
        while (token) {

            token = strtok(NULL, " \t");
        }
    }
    num_filas_arch++;
    fclose(file); 
    printf("Número de filas: %d\n", num_filas_arch);
    printf("Número de columnas: %d\n", num_columnas_arch);

    if (filas == num_filas_arch && cols == num_columnas_arch) {
        return true;
    } else {
        return false;
    }
}

void printmat(int filas, int cols, int** matrix){
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    
}

//funcion que crea (reserva el espacio para las matrices) una matriz
void **crearmatriz(int nfil, int ncol, int*** mat){
    *mat = (int**)malloc(nfil*sizeof(int*));
    if (mat == NULL)
    {
        printf("ERROR: No se ha podido reservar memoria para la matriz!\n");
        exit(1);
    }
    for (int i = 0; i < nfil; i++)
    {
        (*mat)[i] = (int *)malloc(ncol*sizeof(int));
        if ((*mat)[i] == NULL) {
            printf("ERROR: No se ha podido reservar memoria para las cols!\n");
            exit(1);
        }
    }
    
    printf("se ha reservado la memoria para la matriz con exito!\n");
}


//funcion que carga la matriz desde el archivo a memoria
void cargarmatriz(FILE *arch, char *archivo, int filas, int cols, int ***matriz) {
    arch = fopen(archivo, "r");
    if (arch == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char *linea = NULL;
    size_t longitud = 0;
    ssize_t leidos;

    for (int i = 0; i < filas; i++) {
        leidos = getline(&linea, &longitud, arch);
        //printf("el contenido de leidos es: %c\n",leidos);
        if (leidos == -1) {
            perror("Error al leer desde el archivo");
            free(linea);
            fclose(arch);
            exit(EXIT_FAILURE);
        }
        
        char *token = strtok(linea, " ");
        for (int j = 0; j < cols && token != NULL; j++) {
            int valor;
            if (sscanf(token, "%d", &valor) == 1) {
                (*matriz)[i][j] = valor;
            } else {
                perror("Error al convertir token a entero");
                free(linea);
                fclose(arch);
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, " ");
        }
    }
    free(linea);
    printf("Los contenidos del archivo se cargaron exitosamente en memoria\n");
    fclose(arch);
    printf("El archivo se abrió y cerró exitosamente\n");
}

//se crea el numero de procesos 

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
    long num_procesadores = sysconf(_SC_NPROCESSORS_ONLN);
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
    if (numproc%2!=0){
        printf("recuerda que necesito que el numero de procesos sea PAR revisa!\n");
        return -1;
    }
    //verificar que las cols y filas que me pasa el usr y las del arch sean las mismas, si es verdad, 
    //ejecute todo el cuerpo del codigo
    if(filasycolsdelarchivo(archivo,numfils,numcols)){
        //se llama la funcion que reserva el espacio de memoria para la matriz
        crearmatriz(numfils,numcols,&matriz);
        //se llama a la funcion que almacena los elementos en memoria
        cargarmatriz(arch,archivo,numfils,numcols,&matriz);
        //se verifica que el procesador donde se ejecuta el programa, tenga los recursos suficientes,
        //que numproc < #de nucleos del procesasdor
        if (num_procesadores < 1) {
            perror("Error al obtener el número de procesadores");
            return 1;
        } else if (numproc > num_procesadores){
            printf("num procesos: %d\n",numproc);
            printf("num cores: %ld\n",num_procesadores);
            printf("no es posible ejecutar el programa ya que se piden %d procesos y el computador tiene %ld nucleos, me pides mas procesos que nucleos\n",numproc,num_procesadores);
            return -1;
        }
        printmat(numfils,numcols,matriz);
        //se hace la division en grupos de la matriz
        if (numproc%numfils==0) {
            divisionhorizontal(numfils,numproc,&matriz);
        } else if (numproc%numcols==0) {
            divisionvertical(numcols,numproc,&matriz);
        } else {
            divisionirregular(numfils,numproc,&matriz);
        }
        
        
        
        
    } else {
        printf("estas seguro de que pusiste el numero de columnas y filas correcto?\n");
        return -1;
    }
    //se liberan los recursos de memoria usados, empezando por la matriz
    free(matriz);
	return 0;
}
