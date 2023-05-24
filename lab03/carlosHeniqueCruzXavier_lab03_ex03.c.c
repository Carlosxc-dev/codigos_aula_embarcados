#include <stdio.h>
#include <stdlib.h>
#include "carlosHeniqueCruzXavier_lab03_ex03.h"

int main() {
    Scheduler s;
    scheduler_init(&s);
    int q1 = scheduler_add_queue(&s); // adiciona fila q1
    int q2 = scheduler_add_queue(&s);
    scheduler_enqueue(&s, q1, (void *) "Hello"); 
    scheduler_enqueue(&s, q2, (void *) "world");
    void *item;
    while ((item = scheduler_dequeue(&s)) != NULL) {
        printf("%s ", (char *) item);
    }
    printf("\n");

    scheduler(q1, &s, 0); // [0] escalona time_left
    scheduler(q2, &s, 1); // [1] escalona priority

    return 0;
}

void scheduler_init(Scheduler *s) {
    s->num_queues = 0;
}

//add uma nova fila a lista e retorna o indice da nova fila
int scheduler_add_queue(Scheduler *s) {
    if (s->num_queues >= MAX_NUM_QUEUES) {
        return -1;
    }
    Queue *q = &(s->queues[s->num_queues]);
    q->head = 0;
    q->tail = 0;
    s->num_queues++;
    return s->num_queues - 1;
}

//insere um item na cauda da fila
int enqueue(Queue *q, Process *item) {      
    if ((q->tail + 1) % MAX_QUEUE_SIZE == q->head) {
        return -1; // queue is full
    }
    q->processes[q->tail] = item;
    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
    return 0;
}

//remove um elem do inicio da fila
void *dequeue(Queue *q) {
    if (q->head == q->tail) {
        return NULL; // queue is empty
    }
    void *item = q->processes[q->head];
    q->head = (q->head + 1) % MAX_QUEUE_SIZE;
    return item;
}

//busca no vetor de escalonador e add
int scheduler_enqueue(Scheduler *s, int queue_idx, void *item) {
    if (queue_idx < 0 || queue_idx >= s->num_queues) {
        return -1; // invalid queue index
    }
    return enqueue(&(s->queues[queue_idx]), item);
}

//busca no vetor de escalonador e remover
void *scheduler_dequeue(Scheduler *s) {
    int i;
    for (i = 0; i < s->num_queues; i++) {
        Queue *q = &(s->queues[i]);
        void *item = dequeue(q);
        if (item != NULL) {
            return item;
        }
    }
    return NULL; // all queues are empty
}


//escalonar fila q1 pelo time_left
void scheduler(int index, Scheduler *s, int tipo){

    verifica_schedule(index, &s);

    switch (tipo)
    {
    case 1:
        escalona_timeLeft(&(s->queues[index]));
        break;
    case 2:
        escalona_priority(&(s->queues[index]));
        break;
    default:
        printf("opcao invalida\n");
        break;
    }
}

void verifica_schedule(int index, Scheduler *s){
    if (index < 0 || index >= s->num_queues) {
        printf("invalid queue index"); // invalid queue index
        return -1;
    }

    //verifica se escalonador nao tem nenhuma lista 
    if(s->num_queues <= 0 ){
         printf("queue empty");
         return -1;
    }
}

void escalona_timeLeft(Queue *q){
    verifica_queue(&q);

    
}

void verifica_queue(Queue *q){
    if (q->head == q->tail)
    {
        printf("queue esta vazia\n");
        return -1;
    }
    
}
