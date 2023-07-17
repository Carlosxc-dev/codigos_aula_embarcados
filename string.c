#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int arrival_time;
    int execution_time;
    int priority;
    struct Process* next;
} Process;

typedef struct Queue {
    Process* head;
    Process* tail;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

int isQueueEmpty(Queue* queue) {
    return queue->head == NULL;
}

void enqueue(Queue* queue, Process* process) {
    if (isQueueEmpty(queue)) {
        queue->head = process;
        queue->tail = process;
    } else {
        queue->tail->next = process;
        queue->tail = process;
    }
}

Process* dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    Process* process = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL;
    }
    process->next = NULL;
    return process;
}

void multilevel_feedback_queues(Process* processes[], int num_queues, int time_quantum) {
    Queue* queues[num_queues];
    int time = 0;

    for (int i = 0; i < num_queues; i++) {
        queues[i] = createQueue();
    }

    for (int i = 0; i < num_queues; i++) {
        Process* process = processes[i];
        enqueue(queues[0], process);  // Inserir processos na fila de maior prioridade
    }

    while (1) {
        int current_queue = 0;

        while (current_queue < num_queues - 1) {
            Process* process = dequeue(queues[current_queue]);

            if (process != NULL) {
                if (process->execution_time <= time_quantum) {
                    time += process->execution_time;
                    process->execution_time = 0;
                    printf("Process %d completed.\n", process->pid);
                } else {
                    time += time_quantum;
                    process->execution_time -= time_quantum;
                    printf("Process %d time quantum expired.\n", process->pid);
                }
                current_queue++;
                enqueue(queues[current_queue], process);
            } else {
                current_queue++;
            }
        }

        Process* process = dequeue(queues[num_queues - 1]);

        if (process != NULL) {
            time += process->execution_time;
            process->execution_time = 0;
            printf("Process %d completed.\n", process->pid);
        }

        int allQueuesEmpty = 1;
        for (int i = 0; i < num_queues; i++) {
            if (!isQueueEmpty(queues[i])) {
                allQueuesEmpty = 0;
                break;
            }
        }
        if (allQueuesEmpty) {
            break;
        }
    }
}

int main() {
    // Exemplo de uso
    Process* processes[3];

    Process* p1 = (Process*)malloc(sizeof(Process));
    p1->pid = 1;
    p1->arrival_time = 0;
    p1->execution_time = 5;
    p1->priority = 0;
    p1->next = NULL;

    Process* p2 = (Process*)malloc(sizeof(Process));
        p2->pid = 2;
    p2->arrival_time = 0;
    p2->execution_time = 7;
    p2->priority = 1;
    p2->next = NULL;

    Process* p3 = (Process*)malloc(sizeof(Process));
    p3->pid = 3;
    p3->arrival_time = 0;
    p3->execution_time = 10;
    p3->priority = 2;
    p3->next = NULL;

    processes[0] = p1;
    processes[1] = p2;
    processes[2] = p3;

    int num_queues = 3;
    int time_quantum = 3;

    multilevel_feedback_queues(processes, num_queues, time_quantum);

    // Liberar memória alocada
    for (int i = 0; i < 3; i++) {
        free(processes[i]);
    }

    return 0;
}

