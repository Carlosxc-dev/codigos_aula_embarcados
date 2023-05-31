#ifndef PROJETO_H
#define PROJETO_H

#define BUFFER_SIZE 5

// armazena todos os dados pertinentes de cada processo
typedef struct Processo
{
    int data;       // data de criação
    int duracao;    // tempo de execução
    int prioridade; // proridade
} Processo;

// O número de processos presentes no arquivo de entrada deverá ter
// no mínimo o dobro do tamanho do buffer circular.
Processo buffer_proc[BUFFER_SIZE];
int start = 0, end = 0;
int clock_tick = 0; // controle do quantum

void ler_arquivo(Processo *p);
void imprimir_saida(Processo *p, char *text);
void schedule_priority(Processo *p);
void schedule_multiple_queues(Processo *p);
void print_process(Processo *p);

#endif