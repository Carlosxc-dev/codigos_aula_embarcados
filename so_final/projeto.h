#ifndef PROJETO_H
#define PROJETO_H

#define INPUT_SIZE 10
#define BUFFER_SIZE 5
#define MULT_SIZE 2

// armazena todos os dados pertinentes de cada processo
typedef struct Processo
{
    int tempo_chegada;      // data de criação
    int duracao;            // tempo de execução
    int prioridade;         // proridade
} Processo;

typedef struct Input{
    Processo input_processes[INPUT_SIZE];
}Input;

typedef struct Buffer{
    Processo buffer_processes[BUFFER_SIZE];
    int start, end;
}Buffer;

typedef struct Mult_queues{
    Buffer mult_buffer;
    int mult_prioridade;
    int quantum;
    int stop;
}Mult_queues;

int clock_tick = -1; // controle do quantum
int quantum = 0;

void ler_arquivo(Input *p);
void schedule_priority(void *p);
void init_mult_queues(Mult_queues *mult);
int isFullEmpty(Mult_queues *mult_queues, int num);
void add_process_mult(Input *input, Mult_queues *mult_queues, int index);
void kernel_loop(Input *input, Buffer *p_buffer, Mult_queues *mult_queues);

#endif