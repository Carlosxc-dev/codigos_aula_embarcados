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
    int input_start, input_end;
}Input;

typedef struct Buffer{
    Processo buffer_processes[BUFFER_SIZE];
    int start, end;
}Buffer;

typedef struct Mult_queues{
    Buffer buffer_processes[BUFFER_SIZE];
    int mult_start, mult_end;
    int mult_prioridade;
    int quantum;
    int stop;
}Mult_queues;

int clock_tick = -1; // controle do quantum
int quantum = 0;

void ler_arquivo(Input *p);
void imprimir_saida(Processo *p, char *text);
void schedule_priority(void *p);
void schedule_multiple_queues(void *p);
void print_process(void *p, int opc);
void add_process(Input *input, Buffer *p_buffer);
void kernel_loop(Input *input, Buffer *p_buffer, Mult_queues *mult_queues);
void exec_process(Input *input, Buffer *buffer);

#endif