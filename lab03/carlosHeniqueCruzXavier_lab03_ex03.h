#ifndef FILA_H
#define FILA_H

#define MAX_QUEUE_SIZE 100
#define MAX_NUM_QUEUES 10
#define MAX_PROCESSES 10

typedef struct 
{
    int id;
    int priority;
    int time_left;
    int running;
} Process; // PROCESSO

Process processes[MAX_PROCESSES]; // BUFFER DE PROCESSOS 

typedef struct {
    Process *processes[MAX_QUEUE_SIZE];
    int head;
    int tail;
} Queue;  // fila com um buffer 

typedef struct {
    Queue queues[MAX_NUM_QUEUES];
    int num_queues;
} Scheduler;

void scheduler_init(Scheduler *s);
int scheduler_add_queue(Scheduler *s);
int enqueue(Queue *q, Process *item);  
void *dequeue(Queue *q);
int scheduler_enqueue(Scheduler *s, int queue_idx, Process *item);
void *scheduler_dequeue(Scheduler *s);
void scheduler(int index, Scheduler *s, int tipo);
int verifica_schedule(int index, Scheduler *s);
int escalona_timeLeft(Queue *q);
int escalona_priority(Queue *q);
void print_queue(Scheduler *s, int q1, int tipo);


#endif