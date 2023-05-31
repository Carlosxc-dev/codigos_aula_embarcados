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

    if ((end + 1) % BUFFER_SIZE == start)
    {
        printf("lista de processos cheia nao, possivel sobrescrever\n");
        return;
    }

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        // Colocar os valores do arquivo nas variapeis do Processo
        fscanf(f, "%d %d %d", &aux.data, &aux.duracao, &aux.prioridade);
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
        fprintf(o, "\tp[%d] %d %d \n", p[i].data, p[i].duracao, p[i].prioridade);
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

void print_process(Processo *p)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printf("\tp[%d] %d %d \n", p[i].data, p[i].duracao, p[i].prioridade);
    }
}

int main()
{

    ler_arquivo(buffer_proc);
    printf("processos sem escalonamento\n");
    print_process(buffer_proc);

    printf("processos escalonados priority\n");
    schedule_priority(buffer_proc);
    print_process(buffer_proc);

    printf("processos escalonados multiple queues\n");
    schedule_multiple_queues(buffer_proc);
    print_process(buffer_proc);

    printf("\nstart = %d, end = %d\n", end, start);

    imprimir_saida(buffer_proc, "processos escalonado");

    return 0;
}
