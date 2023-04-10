#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
} Process;

float calculate_priority(int waiting_time, int estimated_run_time) {
    return 1 + (float)waiting_time / estimated_run_time;
}

int compare(const void *a, const void *b) {
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return (p1->arrival_time > p2->arrival_time) - (p1->arrival_time < p2->arrival_time);
}

void display_gantt_chart(int gantt_chart[][2], int n) {
    printf("\nGantt Chart:\n |");
    for (int i = 0; i < n; i++) {
        printf("P%d |", gantt_chart[i][0]);
    }
    printf("\n0");
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        current_time += gantt_chart[i][1];
        printf(" %d", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].process_id = i + 1;
    }

    qsort(processes, n, sizeof(Process), compare);

    int time = 0;
    int waiting_times[n];
    int completed_processes = 0;
    int gantt_chart[n][2];

    for (int i = 0; i < n; i++) {
        waiting_times[i] = 0;
    }

    while (completed_processes < n) {
        float max_priority = -1;
        int current_process = -1;
        int burst_time;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time) {
                float priority = calculate_priority(time - processes[i].arrival_time, processes[i].burst_time);
                if (priority > max_priority) {
                    max_priority = priority;
                    current_process = i;
                    burst_time = processes[i].burst_time;
                }
            }
        }

        if (current_process == -1) {
            time++;
            continue;
        }

        waiting_times[current_process] = time - processes[current_process].arrival_time;
        time += burst_time;
        gantt_chart[completed_processes][0] = processes[current_process].process_id;
        gantt_chart[completed_processes][1] = burst_time;
        completed_processes++;

        processes[current_process].arrival_time = INT_MAX;
    }

    display_gantt_chart(gantt_chart, n);

    printf("\nIndividual waiting times: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", waiting_times[i]);
    }

    float average_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        average_waiting_time += waiting_times[i];
    }
    average_waiting_time /= n;

    printf("\nAverage waiting time: %.2f\n", average_waiting_time);

    return 0;
}
