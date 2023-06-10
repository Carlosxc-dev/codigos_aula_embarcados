#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

// ler os dados do arquivo input.txt
void ler_arquivo(Processo *p)
{
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL)
        return;

    if ((end + 1) % FILA_SIZE == start)
    {
        printf("lista de processos cheia nao, possivel sobrescrever\n");
        return;
    }

    for (int i = 0; i < FILA_SIZE; i++)
    {
        // Colocar os valores do arquivo nas variapeis do Processo
        fscanf(f, "%d %d %d", &aux.tempo_chegada, &aux.duracao, &aux.prioridade);
        p[i] = aux;
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
void schedule_priority(Processo *p)
{
    Processo aux;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        for (int j = i + 1; j < BUFFER_SIZE; j++)
        {
            if (p[i].prioridade < p[j].prioridade)
            {
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
        }
    }
}

// Scheduling Multiple queues with feedback
void schedule_multiple_queues(Processo *p)
{
}

// printa os procesos do buffer e da fila
void print_process(Processo *p, int opc)
{
    int max;
    if (opc == 1)
    {
        for (int i = 0; (i < FILA_SIZE); i++)
        {
            printf("\tp %d %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);
            // printf("======= aqui =======\n");
        }
    }
    else
    {
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("\tp %d %d %d \n", p[i].tempo_chegada, p[i].duracao, p[i].prioridade);
            // printf("======= aqui =======\n");
        }
    }
}

// adiona os processos no buffer de acordo com o clock_tick
void add_process(Processo *p_fila, Processo *p_buffer)
{

    for (int i = 0; i < FILA_SIZE; i++)
    {
        if ((p_fila[i].tempo_chegada <= clock_tick)&&((end+1) != start))
        {
            // printf("adicionando buffer[%d] processo[%d] \n", end, p_fila[i].tempo_chegada);
            p_buffer[end] = p_fila[i];
            end = (end + 1) % BUFFER_SIZE;
        }
    }
}

// looping infinido
void kernel_loop(void)
{
    for (;;)
    {
        clock_tick++;
        add_process(fila_proc, buffer_proc);
        // schedule_priority(buffer_proc);
        print_process(buffer_proc, 2);
        printf("--------------------------- clock time %d\n", clock_tick);
        end = 0;        //serve pra printar todos processos corretamente 
        if (clock_tick >= 10)
        {
            break;
        }
    }
}

int main()
{

    ler_arquivo(fila_proc);
    printf("processos sem escalonamento\n");
    print_process(fila_proc, 1);

    printf("processos escalonados priority\n");
    // add_process(fila_proc, buffer_proc);
    // schedule_priority(buffer_proc);
    // print_process(buffer_proc, 2);

    // printf("\nstart = %d, end = %d\n", start, end);

    // imprimir_saida(buffer_proc, "processos escalonado");

    kernel_loop();

    return 0;
}
