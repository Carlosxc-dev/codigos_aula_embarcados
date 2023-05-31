#ifndef PROJETO_H
#define PROJETO_H

#define BUFFER_SIZE 10

// armazena todos os dados pertinentes de cada processo
typedef struct Processo
{
    int data;       // data de criação
    int duracao;    // tempo de execução
    int prioridade; //proridade
} Processo;



void ler_arquivo(Processo *p);
void imprimir_saida(Processo *p);




#endif