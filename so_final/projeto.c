#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

// ler os dados do arquivo input.txt
void ler_arquivo(Input *p)
{
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL)
        return;

    for (int i = 0; i < INPUT_SIZE; i++)
    {
        // Colocar os valores do arquivo nas variapeis do Processo
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        p->input_processes[i] = aux;
    }
    fclose(f);
}

// Priority-based Scheduling
void schedule_priority(void *p)
{
    Processo *proc = (Processo *)p;
    Processo aux;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        for (int j = i + 1; j < BUFFER_SIZE; j++)
        {
            if (proc[i].prioridade < proc[j].prioridade)
            {
                aux = proc[i];
                proc[i] = proc[j];
                proc[j] = aux;
            }
        }
    }
}


//-------------------------mult queues-----------------------------------
void init_mult_queues(Mult_queues *mult){
    mult[0].mult_prioridade = 1;
    mult[0].quantum = 2;
    mult[0].stop = 0;

    mult[1].mult_prioridade = 2;
    mult[1].quantum = 4;
    mult[1].stop = 0;
    // printf("[%d]\n", mult[1].quantum);
}

int isFullEmpty(Mult_queues *mult_queues, int num)
{
    if ((mult_queues[num].mult_buffer.end + 1) % BUFFER_SIZE == mult_queues[num].mult_buffer.start)
        return -1;
    else
        return 0;
}

// add proccess
void add_process_mult(Input *input, Mult_queues *mult_queues, int index)
{

    if (isFullEmpty(mult_queues, index) == 0) // verifica se fila x esta vazia
    { 
        
    }
}

// looping infinido
void kernel_loop(Input *input, Buffer *p_buffer, Mult_queues *mult_queues)
{
    for (;;)
    {
        add_process_mult(input, mult_queues, 0);
        exec_proc();


        if (clock_tick >= 10)
            break;
    }
}

int main()
{

    Input input_proc;                  // processos vindos do input.txt
    Mult_queues mult_filas[MULT_SIZE]; // crio as duas filas

    printf("processos sem escalonamento\n");
    ler_arquivo(&input_proc);
    
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        printf("\tp %d %d %d\n", input_proc.input_processes[i].tempo_chegada, 
            input_proc.input_processes[i].duracao, input_proc.input_processes[i].prioridade);
    }
    
        printf("inicializando mult filas\n");
        init_mult_queues(mult_filas);
        for (int i = 0; i < MULT_SIZE; i++)
    {
        printf("\tf[%d] %d %d %d\n", i, mult_filas[i].mult_prioridade, 
            mult_filas[i].quantum, mult_filas[i].stop);
    }

    printf("processos escalonados multiplas filas\n");
    kernel_loop(&input_proc, mult_filas, 0);

    return 0;
}
