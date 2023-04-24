#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} process;

int main() {
    int n, quantum, total_time = 0, total_wait_time = 0, total_turnaround_time = 0;
    process processes[MAX_PROCESSES];
    printf("Ingrese el número de procesos: ");
    scanf("%d", &n);
    printf("Ingrese el tiempo de ráfaga para cada proceso:\n");
    for (int i = 0; i < n; i++) {
        printf("Proceso %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
        processes[i].arrival_time = total_time;
        processes[i].remaining_time = processes[i].burst_time;
        total_time += processes[i].burst_time;
    }
    printf("Ingrese el tamaño del quantum: ");
    scanf("%d", &quantum);
    int time = 0;
    while (1) {
        int completed = 1;
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                completed = 0;
                if (processes[i].remaining_time > quantum) {
                    processes[i].remaining_time -= quantum;
                    time += quantum;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    int wait_time = time - processes[i].arrival_time - processes[i].burst_time;
                    int turnaround_time = time - processes[i].arrival_time;
                    total_wait_time += wait_time;
                    total_turnaround_time += turnaround_time;
                    printf("Proceso %d completado en tiempo %d, espera %d, tiempo de retorno %d\n", processes[i].id, time, wait_time, turnaround_time);
                }
            }
        }
        if (completed) {
            break;
        }
    }
    printf("Tiempo de espera promedio: %f\n", (float) total_wait_time / n);
    printf("Tiempo de retorno promedio: %f\n", (float) total_turnaround_time / n);
    return 0;
}

