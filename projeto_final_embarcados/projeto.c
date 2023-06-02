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

//printa os procesos do buffer e da fila
void print_process(Processo *p, int opc)
{
    int max;
    if (opc == 1){
        max = FILA_SIZE;
    }else{
        max = end;
    }
    
    for (int i = 0; i < max; i++)
    {
        printf("\tp[%d] %d %d \n", p[i].data, p[i].duracao, p[i].prioridade);
    }
}

//adiona os processos no buffer de acordo com o clock_tick
void add_process(Processo *p_fila, Processo *p_buffer){

    
    for (int i = 0; i < FILA_SIZE; i++)
    {
        if (p_fila[i].data <= clock_tick )
        {
            p_buffer[end] = p_fila[i];
            printf("%d\n", p_buffer[end].data);
            end = (end+1) % BUFFER_SIZE;
        }
    }
}

//

int main()
{

    ler_arquivo(fila_proc);
    printf("processos sem escalonamento\n");
    print_process(fila_proc, 1);
    add_process(fila_proc, buffer_proc);

    printf("processos escalonados priority\n");
    schedule_priority(buffer_proc);
    print_process(buffer_proc, 2);

    // printf("processos escalonados multiple queues\n");
    // schedule_multiple_queues(buffer_proc);
    // print_process(buffer_proc);

    printf("\nstart = %d, end = %d\n", start, end);

    imprimir_saida(buffer_proc, "processos escalonado");

    return 0;
}
