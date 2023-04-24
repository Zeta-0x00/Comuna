#include <stdio.h>

// Estructura para representar un proceso
typedef struct {
    char name[100];
    int priority;
    int burstTime;
    int remainingTime;
} Process;

// Función para ejecutar un proceso con el algoritmo de multinivel
void executeProcess(Process *processes, int numProcesses) {
    int currentTime = 0;

    // Ejecutar procesos en base a su prioridad
    for (int i = 0; i < numProcesses; i++) {
        // Verificar si el proceso ya se completó
        if (processes[i].remainingTime == 0) {
            continue; // Pasar al siguiente proceso si ya se completó
        }

        // Ejecutar proceso actual
        printf("Tiempo actual: %d, Proceso: %s\n", currentTime, processes[i].name);
        processes[i].remainingTime--;

        // Actualizar el tiempo actual
        currentTime++;

        // Verificar si el proceso actual aún tiene tiempo restante
        if (processes[i].remainingTime > 0) {
            i--; // Volver a ejecutar el mismo proceso si aún tiene tiempo restante
        }
    }
}

int main() {
    // Crear un arreglo de procesos
    Process processes[] = {
        {"P1", 2, 4, 4},
        {"P2", 1, 6, 6},
        {"P3", 3, 2, 2}
    };

    int numProcesses = sizeof(processes) / sizeof(Process);

    // Ejecutar procesos con el algoritmo de multinivel
    executeProcess(processes, numProcesses);

    return 0;
}

