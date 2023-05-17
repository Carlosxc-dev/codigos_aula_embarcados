#include <stdio.h>
#include "lab2.h"

void main() {
    //Process exemplo = {id, priority, time_left, running};
    Process p1 = {1, 5, 7, 0};
    Process p2 = {2, 9, 2, 0};
    Process p3 = {3, 2, 5, 0};
    Process p4 = {4, 3, 3, 0};
    Process p5 = {5, 7, 9, 0};

    create_process(&p1);
    create_process(&p2);
    create_process(&p3);
    create_process(&p4);
    create_process(&p5);

    set_priority(1, 3);
    set_priority(5, 12);

    schedule_next_process();
    printf("\n");
    terminate_process();
    printf("\n\n");
}

void print() {
    if (current_process > -1)
        printf("\nstart %d: process %d: priority %d", current_process, processes[current_process].id, processes[current_process].priority);
}
char create_process(void *data) {
    Process *params = (Process *)data;

    if ((end_process + 1) % BUFFERSIZE == current_process) {
        printf("Maximum number of processes reached\n");
        return FAIL;
    }

    Process criado = {params->id, params->priority, params->time_left, params->running};
    processes[end_process] = criado;
    printf("\nProcesso %d criado", processes[end_process].id);
    num_processes++;
    end_process++;
    return SUCESS;
}
void set_priority(int id, int priority) {
    int i = current_process;

    while (i != end_process)
    {
        if (processes[i].id == id)
        {
            processes[i].priority = priority;
            return;
        }
        i = (i + 1) % BUFFERSIZE;
    }
    printf("Process not found\n");
}
void terminate_process() {
    if (current_process == end_process) {
        printf("Empty list");
        return;
    }
    while (current_process != end_process) {
        print();
        processes[current_process].running = 1; // já foi processado
        current_process = (current_process + 1) % BUFFERSIZE;
        schedule_next_process();
    }
}
void schedule_next_process() {
    int next;
    int j = (current_process + 1) % BUFFERSIZE;
    Process swap;

    if (current_process != end_process) {
        next = current_process;
        while (j != end_process) {
            if (processes[j].time_left < processes[next].time_left)
                next = j;
            j = (j + 1) % BUFFERSIZE;
        }

        // troca de processos
        swap = processes[next];
        processes[next] = processes[current_process];
        processes[current_process] = swap;
    }
}