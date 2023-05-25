#include <stdio.h>
#include <stdlib.h>
#include "carlosHeniqueCruzXavier_lab03_ex03.h"

int main()
{
    Scheduler s;
    scheduler_init(&s);
    int q1 = scheduler_add_queue(&s); // adiciona fila q1
    int q2 = scheduler_add_queue(&s); // adiciona fila q2

    //criando processos pra fila [1]
    //id - priority - time_left - running;
    Process p1 = {0, 0, 11, 0};
    Process p2 = {1, 0, 13, 0};
    Process p3 = {2, 0, 14, 0};
    Process p4 = {3, 0, 12, 0};
    Process p5 = {4, 0, 10, 0};
    scheduler_enqueue(&s, q1, &p1);
    scheduler_enqueue(&s, q1, &p2);
    scheduler_enqueue(&s, q1, &p3);
    scheduler_enqueue(&s, q1, &p4);
    scheduler_enqueue(&s, q1, &p5);

    //criando processos pra fila [2]
    //id - priority - time_left - running;
    Process p6 = {0, 1, 0, 0};
    Process p7 = {1, 4, 0, 0};
    Process p8 = {2, 2, 0, 0};
    Process p9 = {3, 3, 0, 0};
    Process p10= {4, 5, 0, 0};
    scheduler_enqueue(&s, q2, &p6);
    scheduler_enqueue(&s, q2, &p7);
    scheduler_enqueue(&s, q2, &p8);
    scheduler_enqueue(&s, q2, &p9);
    scheduler_enqueue(&s, q2, &p10);

    
    printf("processos criados sem escalonamento fila 1 e 2\n");
    print_queue(&s, q1, 1); 
    print_queue(&s, q2, 2); 
    printf("\n");

    printf("processos escalonados por time_left\n");
    scheduler(q1, &s, 1); // [1] escalona time_left
    print_queue(&s, q1, 1); // printa fila
    printf("\n");

    printf("processos escalonados por priority\n");
    scheduler(q2, &s, 2); // [2] escalona priority
    print_queue(&s, q2, 2); // printa fila
    printf("\n");

    return 0;
}

void print_queue(Scheduler *s, int idx, int tipo)
{
    int j = s->queues[idx].head; // Inicializa j com o valor de head

    while (j != s->queues[idx].tail)
    {
        if (tipo == 1){
            printf("Fila [1] processo [%d] - ", s->queues[idx].processes[j]->id);
            printf("time_left [%d]\n", s->queues[idx].processes[j]->time_left);
        }else{
            printf("Fila [2] processo [%d] - ", s->queues[idx].processes[j]->id);
            printf("priority [%d]\n", s->queues[idx].processes[j]->priority);
        }
        j = (j + 1) % MAX_QUEUE_SIZE;
    }
}

void scheduler_init(Scheduler *s)
{
    s->num_queues = 0;
}

// add uma nova fila a lista e retorna o indice da nova fila
int scheduler_add_queue(Scheduler *s)
{
    if (s->num_queues >= MAX_NUM_QUEUES)
    {
        return -1;
    }
    Queue *q = &(s->queues[s->num_queues]);
    q->head = 0;
    q->tail = 0;
    s->num_queues++;
    return s->num_queues - 1;
}

// insere um item na cauda da fila
int enqueue(Queue *q, Process *item)
{
    if ((q->tail + 1) % MAX_QUEUE_SIZE == q->head)
    {
        return -1; // queue is full
    }
    q->processes[q->tail] = item;
    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
    return 0;
}

// remove um elem do inicio da fila
void *dequeue(Queue *q)
{
    if (q->head == q->tail)
    {
        return NULL; // queue is empty
    }
    void *item = q->processes[q->head];
    q->head = (q->head + 1) % MAX_QUEUE_SIZE;
    return item;
}

// busca no vetor de escalonador e add
int scheduler_enqueue(Scheduler *s, int queue_idx, Process *item)
{
    if (queue_idx < 0 || queue_idx >= s->num_queues)
    {
        return -1; // invalid queue index
    }
    return enqueue(&(s->queues[queue_idx]), item);
}

// busca no vetor de escalonador e remover
void *scheduler_dequeue(Scheduler *s)
{
    int i;
    for (i = 0; i < s->num_queues; i++)
    {
        Queue *q = &(s->queues[i]);
        void *item = dequeue(q);
        if (item != NULL)
        {
            return item;
        }
    }
    return NULL; // all queues are empty
}

//verifica se as listas estao vazias 
int verifica_schedule(int index, Scheduler *s)
{
    if (index < 0 || index >= s->num_queues)
    {
        printf("invalid queue index"); // invalid queue index
        return -1;
    }

    // verifica se escalonador nao tem nenhuma lista
    if (s->num_queues <= 0)
    {
        printf("queue empty");
        return -1;
    }
}

// escalonar fila q1 pelo time_left
void scheduler(int index, Scheduler *s, int tipo)
{
    if (verifica_schedule(index, s) == -1)
    {
        return; // Encerra a função se a validação falhar
    }

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

int escalona_timeLeft(Queue *q)
{

    if (q->head == q->tail)
    {
        printf("queue esta vazia\n");
        return -1;
    }

    Process *aux;
    for (int i = 0; i < q->tail; i++)
    {
        for (int j = i + 1; j < q->tail; j++)
        {
            if (q->processes[i]->time_left > q->processes[j]->time_left)
            {
                aux = q->processes[i];
                q->processes[i] = q->processes[j];
                q->processes[j] = aux;
            }
        }
    }
}

int escalona_priority(Queue *q)
{
    if (q->head == q->tail)
    {
        printf("queue esta vazia\n");
        return -1;
    }

    Process *aux;
    for (int i = 0; i < q->tail; i++)
    {
        for (int j = i + 1; j < q->tail; j++)
        {
            if (q->processes[i]->priority < q->processes[j]->priority)
            {
                aux = q->processes[i];
                q->processes[i] = q->processes[j];
                q->processes[j] = aux;
            }
        }
    }
}

