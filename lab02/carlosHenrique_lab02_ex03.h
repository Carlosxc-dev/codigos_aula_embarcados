#ifndef PROCESS_H
#define PROCESS_H

// RETORNOS DAS FUNCOES
#define SUCESS 0
#define FAIL 1
#define REPEAT 2

// TAMAHO DO BUFFERS
#define BUFFER_SIZE 10
#define MIN_INT -30000

// dados do processo
typedef struct
{
    int id;
    int prioridade;
    int time_left; // tempo que leva ate ser executado
    int running;
    int periodo;     // periodo ate a execucao da tarefa
    int count_start; // contador para verificação da execução da atividade
} Process;

// variaveis de controle
int num_processo = 0;
int atual_processo;
int start = 0, end = 0;
Process buffer_proc[BUFFER_SIZE]; // buffer

// funcoes do kernel
char create_process(void *proc);
void set_priority(int id, int priority);
void terminate_process(int id);
void schedule_next_process();
void kernelLoop(void);
void KernelClock(void);
char kernelAddProc(Process* new_proc);
void print_proc(void);

#endif