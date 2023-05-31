#include <stdio.h>
#include <stdlib.h>
#include "projeto.h"

// ler os dados do arquivo input.txt
void ler_arquivo(Processo *p)
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
        return;

    for (int i = 0; i < MAX; i++)
    {
        // Colocar os valores do arquivo nas variapeis do Processo
        fscanf(f, "%d %d %d", &p[i].data, &p[i].duracao, &p[i].prioridade);
        
    }

    fclose(f);
}

// imprime a saida do programa no arquivo output.txt
void imprimir_saida(Processo *p)
{
    FILE *o = fopen("output.txt", "w");

    for (int i = 0; i < MAX; i++)
    {
        fprintf(o, "p[%d] %d %d \n", p[i].data, p[i].duracao, p[i].prioridade);
        printf("%d ", p[i].prioridade);
    }
    
    // fechando aquivo de saida output.txt
    fclose(o);
}

int main()
{
    Processo p[MAX];

    ler_arquivo(p);
    imprimir_saida(p);
    


    return 0;

}
