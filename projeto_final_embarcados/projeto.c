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

    if ((p->input_end + 1) % INPUT_SIZE == p->input_start)
    {
        printf("lista de processos cheia nao, possivel sobrescrever\n");
        return;
    }

    for (int i = 0; i < INPUT_SIZE; i++)
    {
        // Colocar os valores do arquivo nas variapeis do Processo
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        p->input_processes[i] = aux;
    }
    fclose(f);
}

// imprime a saida do programa no arquivo output.txt
void imprimir_saida(Processo *p, char *text)
{
    FILE *o = fopen("output.txt", "w");
    fprintf(o, "%s \n", text);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        fprintf(o, "\tp[%d] %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);
    }

    // fechando aquivo de saida output.txt
    fclose(o);
}

// Priority-based Scheduling
void schedule_priority(void *p)
{
    Processo *proc = (Processo*) p;
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

// printa os procesos do buffer e da fila
void print_process(void *p, int opc)
{
    int max;
    if (opc == 1)
    {
        Input *aux = (Input*) p;
        for (int i = 0; (i < INPUT_SIZE); i++)
        {
            printf("\tp %d %d %d \n", aux->input_processes[i].tempo_chegada, 
            aux->input_processes[i].duracao, aux->input_processes[i].prioridade);
        }
    }
    else
    {
        Buffer *aux = (Buffer*) p;
        for (int i = aux->start; i < aux->end; i++)
        {
            printf("\tp %d %d %d \n", aux->buffer_processes[i].tempo_chegada,
             aux->buffer_processes[i].duracao, aux->buffer_processes[i].prioridade);
        }
    }
}

// adiona os processos no buffer de acordo com o clock_tick
void add_process(Input *input, Buffer *p_buffer)
{
    for (int i = 0; i < INPUT_SIZE; i++)
    {
        if ((input->input_processes[i].tempo_chegada <= clock_tick)&&
            (((p_buffer->end+1)%BUFFER_SIZE) != p_buffer->start))
        {
            // printf("adicionando buffer[%d] processo[%d] end[%d] start[%d]\n", 
            //     p_buffer->end, input->input_processes[i].tempo_chegada,
            //     p_buffer->end, p_buffer->start);

            p_buffer->buffer_processes[p_buffer->end] = input->input_processes[i];
            p_buffer->end = (p_buffer->end + 1) % BUFFER_SIZE;
        }
    }
}

// void exec_process(Input *input, Buffer *buffer){
//     if (((buffer->end+1)%BUFFER_SIZE) != buffer->start) // buffer nao esta vazio
//     {
//         for (int i = buffer->start; i < buffer->end; i++)
//         {   
//             if (buffer->buffer_processes[i].duracao <= clock_tick)
//             {
//                 buffer->start += 1 % BUFFER_SIZE; // "remove" do buffer
//                 printf("rem - processo [%d] duracao[%d] clock[%d]\n", buffer->start,
//                     buffer->buffer_processes[i].duracao, clock_tick);
//             }
//         }
//     }
// }


//-------------------------mult queues-----------------------------------
void init_mult_queues(Mult_queues *mult){
    mult[0].buffer_processes->end = 0;
    mult[0].buffer_processes->start = 0;
    mult[0].mult_prioridade = 1;
    mult[0].quantum = 2;
    mult[0].stop = 0;

    mult[1].buffer_processes->end = 0;
    mult[1].buffer_processes->start = 0;
    mult[1].mult_prioridade = 2;
    mult[1].quantum = 4;
    mult[1].stop = 0;
    // printf("[%d]\n", mult[1].quantum);
}

int isFullEmpty(Mult_queues *mult_queues, int num){
    if ((mult_queues[num].mult_end + 1)%BUFFER_SIZE  == mult_queues[num].mult_start) return -1;
    else return 0;
}

//add proccess
void add_process_mult(Input *input, Mult_queues *mult_queues, int index){
    
    if(isFullEmpty(mult_queues, index) == 0){ //verifica se fila x esta vazia
       for (int i = 0; i < INPUT_SIZE; i++)
       {
            if ( input->input_processes[i].tempo_chegada <= clock_tick)
            {
                mult_queues->buffer_processes[index].buffer_processes[mult_queues->stop] = input->input_processes[i];
                mult_queues->stop++;
                printf("add proc[%d] stop[%d] \n", mult_queues[index].buffer_processes[mult_queues->stop].buffer_processes[i].duracao,
                                                     mult_queues->stop);
            }
       }
    }
}

// Scheduling Multiple queues with feedback
void schedule_multiple_queues(void *p)
{
}
// looping infinido
void kernel_loop(Input *input, Buffer *p_buffer, Mult_queues *mult_queues)
{
    for (;;)
    {
        // add_process(input, p_buffer);
        add_process_mult(input, mult_queues, 0);
        // exec_process(input, p_buffer);
        // print_process(p_buffer, 2);
        // printf("--------------------------- clock time %d\n", clock_tick);
        clock_tick = 1;
        p_buffer->end = 0;        //serve pra printar todos processos corretamente 
        if (clock_tick >= 10)
        {
            break;
        }
    }
}

int main()
{
    
    // O número de processos presentes no arquivo de entrada deverá ter
    // no mínimo o dobro do tamanho do buffer circular.
    Input input_proc;    // processos vindos do input 
    Buffer buffer_proc;  // vetor que sofre escalonamento
    buffer_proc.start = 0;
    Mult_queues mult_filas[MULT_SIZE]; //crio as duas filas

    ler_arquivo(&input_proc);
    printf("processos sem escalonamento\n");
    print_process(&input_proc, 1);
    // printf("processos escalonados priority\n");

    printf("processos escalonados multiplas filas\n");
    init_mult_queues(mult_filas);

    kernel_loop(&input_proc, &buffer_proc, mult_filas);

    return 0;
}
