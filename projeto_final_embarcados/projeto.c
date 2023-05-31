#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"
int start=0, end=0;

// ler os dados do arquivo input.txt
void ler_arquivo(Processo *p)
{
    FILE *f = fopen("input.txt", "r");
    Processo aux;

    if (f == NULL) return;

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
void imprimir_saida(Processo *p)
{
    FILE *o = fopen("output.txt", "w");

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        fprintf(o, "p[%d] %d %d \n", p[i].data, p[i].duracao, p[i].prioridade);
        printf("%d ", p[i].data);
    }
    
    // fechando aquivo de saida output.txt
    fclose(o);
}

//Priority-based Scheduling
void schedule_priority(Processo *p){
    
    Processo aux;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        for (int j = i+1; j < BUFFER_SIZE; j++)
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

int main()
{
    Processo buffer_proc[BUFFER_SIZE];

    ler_arquivo(buffer_proc);
    
    schedule_priority(buffer_proc);

    imprimir_saida(buffer_proc);
    


    return 0;

}
