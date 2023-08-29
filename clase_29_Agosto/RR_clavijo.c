#include <stdio.h>

// Definir la cantidad de procesos
#define NUM_PROCESOS 5

// Definir el quantum time
#define QUANTUM_TIME 2

// Estructura para representar un proceso, tiene todos los datos relevantes que pide el problema
typedef struct {
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Proceso;

int main() {
    Proceso procesos[NUM_PROCESOS] = { //matriz de tipo proceso que tiene los datos de procesos con sus tiempos de llegada y rafaga
        {1, 4, 4, 0, 0, 0},
        {2, 6, 6, 0, 0, 0},
        {3, 7, 7, 0, 0, 0},
        {4, 8, 8, 0, 0, 0},
        {5, 5, 5, 0, 0, 0}
    };

    int tiempo_actual = 0;
    int procesos_restantes = NUM_PROCESOS;

    while (procesos_restantes > 0) { // while que simula round robin, no termina hasta que los procesos hallan sido completados
        for (int i = 0; i < NUM_PROCESOS; i++) { 
            Proceso *p = &procesos[i];
            if (p->remaining_time > 0) { 
                int tiempo_ejecucion = QUANTUM_TIME < p->remaining_time ? QUANTUM_TIME : p->remaining_time; 
                tiempo_actual += tiempo_ejecucion; //Se actualiza el tiempo_actual con el tiempo de ejecución calculado y se decrementa el remaining_time del proceso correspondiente.
                p->remaining_time -= tiempo_ejecucion; 

                if (p->remaining_time == 0) { //Si el remaining_time del proceso se reduce a cero, se actualizan los tiempos completion_time, turnaround_time y waiting_time del proceso. También se decrementa procesos_restantes para indicar que un proceso ha sido completado.
                    p->completion_time = tiempo_actual;
                    p->turnaround_time = p->completion_time - p->arrival_time;
                    p->waiting_time = p->turnaround_time - p->burst_time;
                    procesos_restantes--;
                }
            }
        }
    }

    printf("Proceso\tCompletion Time\tTurnaround Time\tWaiting Time\n"); //impresion de columnas para la table
    for (int i = 0; i < NUM_PROCESOS; i++) { //bucle donde se imprime la tabla
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, procesos[i].completion_time, procesos[i].turnaround_time, procesos[i].waiting_time);
    }

    return 0;
}
