
/*
Modifique o exercício 2 para trabalhar com ponteiros de função e/ou
ponteiros para void. A estrutura do buffer circular deve permitir a inserção e
remoção de elementos de forma que o buffer não se sobrescreva. Também
deve ser capaz de armazenar elementos de tamanho variável e ter tamanho
fixo

Modifique a estrutura anterior de modo que ela utilize requisitos temporais
para o funcionamento do escalonador, isto é, ela deve possuir em sua estrutura
a definição de período de execução da atividade (variável period) e um
contador para verificação da execução da atividade (variável start). A partir
destes requisitos de tempo, reescreva o novo núcleo do kernel de modo que a
execução das atividades ocorra de acordo com a métrica Earliest Dealine First
(EDF).

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "carlosHenrique_lab02_ex03.h"

char create_process(void *proc)
{
    Process *processo = (Process *)proc; // casting void pointer

    if ((end + 1) % BUFFER_SIZE == start)
    {
        printf("lista de processos cheia nao, possivel sobrescrever\n");
        return FAIL;
    }

    // adiciono processo no buffer
    buffer_proc[end] = *processo;
    printf("processo criado %d\n", end);

    // atualiza variaveis
    num_processo++;
    end = (end + 1) % BUFFER_SIZE;
    return SUCESS;
}

void set_priority(int id, int priority)
{
    for (int i = 0; i < num_processo; i++)
    {
        if (buffer_proc[i].id == id)
        {
            buffer_proc[i].prioridade = priority;
            return;
        }
    }
    printf("Process not found\n");
}

void terminate_process(int id)
{
    if (start != end)
    {
        for (int i = 0; i < num_processo; i++)
        {
            if (buffer_proc[i].id == id)
            {
                buffer_proc[i].running = 1; // foi executado
                return;
            }
        }
        start = (start+1)%BUFFER_SIZE;
    }
    printf("buffer esta vazio...\n");
}

void schedule_next_process()
{
     int next = -1;
    
    if(start != end)
    {
        next = start;
        int j = (start + 1) % BUFFER_SIZE;

        while(j != end)
        {
            if(buffer_proc[j].time_left < buffer_proc[next].time_left){
                next = j;
            }
            j = (j + 1) % BUFFER_SIZE;
        }

        Process* aux = &buffer_proc[next];
        buffer_proc[next] = buffer_proc[start];
        buffer_proc[start] = *aux;

        start = (start + 1) % BUFFER_SIZE;
    }
}

char kernelAddProc(Process* new_proc)
{
    if(((end + 1) % BUFFER_SIZE) != start)
    {
        buffer_proc[end] = *new_proc;
        buffer_proc[end].count_start += new_proc->periodo;
        end = (end + 1) % BUFFER_SIZE;
        return SUCESS;
    }

    return FAIL;
}

void kernelLoop(void)
{
    for (;;){
        if (start != end){
            if (buffer_proc[start].running== REPEAT){
                kernelAddProc(&buffer_proc[start]);
            }
            start = (start + 1) % BUFFER_SIZE;
        }
    }
}

void KernelClock(void)
{
    unsigned char i;
    i = start;
    while (i != end)
    {
        if ((buffer_proc[i].count_start) > (MIN_INT))
        {
            buffer_proc[i].count_start--;
        }
        i = (i + 1) % BUFFER_SIZE;
    }
}

void print_proc(void){
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (i != end)
        {
            printf("processo %d\n", buffer_proc[i].id);
        }
    }
}

int main(int argc, char const *argv[])
{
    // processos para ser escalonadosid;
    //id,  prioridade, time_left, running, periodo, count_start
    Process p0 = {0, 0, 9, 0, 0};
    Process p1 = {1, 0, 8, 0, 0};
    Process p2 = {2, 0, 7, 0, 0};
    Process p3 = {3, 0, 6, 0, 0};
    Process p4 = {4, 0, 1, 0, 0};
    Process p5 = {5, 0, 4, 0, 0};
    Process p6 = {6, 0, 3, 0, 0};
    Process p7 = {7, 0, 2, 0, 0};
    Process p8 = {8, 0, 9, 0, 0};

    // adicionando processo ao buffers
    printf("criando processos e adicionando no buffers\n");
    create_process(&p0);
    create_process(&p1);
    create_process(&p2);
    create_process(&p3);
    create_process(&p4);
    create_process(&p5);
    create_process(&p6);
    create_process(&p7);
    create_process(&p8);
    printf("--------------------------\n");


    printf("processos no buffers sem escalonar\n");
    print_proc();
    printf("--------------------------\n");

    printf("processos no buffers escalonado\n");
    schedule_next_process();
    print_proc();

    kernelLoop();



    return 0;
}
