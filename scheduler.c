#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct job {
    char *name;
    int estimated_time;
    int waiting_time;
    float priority;
} Job;

void update_priority(Job *job) {
    job->priority = 1 + (float) job->waiting_time / job->estimated_time;
}

void schedule(Job **jobs, int n_jobs) {
    int time = 0;
    Job **waiting_jobs = malloc(n_jobs * sizeof(Job *));
    memcpy(waiting_jobs, jobs, n_jobs * sizeof(Job *));
    Job **completed_jobs = malloc(n_jobs * sizeof(Job *));
    int n_completed_jobs = 0;

    while (n_completed_jobs < n_jobs) {
        float max_priority = -1;
        Job *max_priority_job = NULL;

        for (int i = 0; i < n_jobs; i++) {
            Job *job = waiting_jobs[i];
            if (job != NULL) {
                if (job->priority > max_priority) {
                    max_priority = job->priority;
                    max_priority_job = job;
                }
            }
        }

        printf("Time %d: Running job %s\n", time, max_priority_job->name);

        for (int t = 0; t < max_priority_job->estimated_time; t++) {
            time++;
            max_priority_job->waiting_time = time - max_priority_job->estimated_time;
            for (int i = 0; i < n_jobs; i++) {
                Job *job = waiting_jobs[i];
                if (job != NULL && job != max_priority_job) {
                    job->waiting_time++;
                    update_priority(job);
                }
            }
            update_priority(max_priority_job);
            printf("Time %d: %s(%g)\n", time, max_priority_job->name, max_priority_job->priority);
        }

        completed_jobs[n_completed_jobs] = max_priority_job;
        waiting_jobs[max_priority_job - jobs] = NULL;
        n_completed_jobs++;
    }

    int total_waiting_time = 0;
    for (int i = 0; i < n_jobs; i++) {
        total_waiting_time += completed_jobs[i]->waiting_time;
    }
    float avg_waiting_time = (float) total_waiting_time / n_jobs;

    printf("Gantt chart:\n");
    for (int i = 0; i < n_jobs; i++) {
        printf("%s ", completed_jobs[i]->name);
    }
    printf("\n");

    printf("Individual waiting times:\n");
    for (int i = 0; i < n_jobs; i++) {
        printf("%s: %d\n", completed_jobs[i]->name, completed_jobs[i]->waiting_time);
    }
    printf("Average waiting time: %g\n", avg_waiting_time);

    free(waiting_jobs);
    free(completed_jobs);
}

int main() {
    int n_jobs = 0;
    Job **jobs = malloc(sizeof(Job *));

    while (1) {
        char name[100];
        printf("Enter job name (or 'done' to finish): ");
        scanf("%s", name);
        if (strcmp(name, "done") == 0) {
            break;
        }
        int estimated_time;
        printf("Enter estimated run time: ");
        scanf("%d", &estimated_time);
        Job *job = malloc(sizeof(Job));
        job->name = strdup(name);
        job->estimated_time = estimated_time;
        job->waiting_time = 0;
        job->priority = 1;
        n_jobs++;
        jobs = realloc(jobs, n_jobs * sizeof(Job *));
       
    }
}
