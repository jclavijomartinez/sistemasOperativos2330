#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generarMatriz(int filas, int columnas, float porcentajeUnos) {
    int totalElementos = filas * columnas;
    int totalUnos = totalElementos * porcentajeUnos;
    int matriz[filas][columnas];

    // Inicializar la matriz con ceros
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0;
        }
    }

    // Rellenar la matriz con unos
    for (int k = 0; k < totalUnos; k++) {
        int filaRandom, columnaRandom;
        do {
            filaRandom = rand() % filas;
            columnaRandom = rand() % columnas;
        } while (matriz[filaRandom][columnaRandom] == 1);

        matriz[filaRandom][columnaRandom] = 1;
    }

    // Imprimir la matriz
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int filas, columnas;
    float porcentaje;

    srand(time(NULL)); // Inicializar la semilla para números aleatorios

    printf("Introduce el número de filas: ");
    scanf("%d", &filas);
    printf("Introduce el número de columnas: ");
    scanf("%d", &columnas);
    printf("Introduce el porcentaje de unos (ejemplo: 0.5 para 50%%): ");
    scanf("%f", &porcentaje);

    generarMatriz(filas, columnas, porcentaje);

    return 0;
}
