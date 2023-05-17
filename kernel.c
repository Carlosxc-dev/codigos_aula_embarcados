#include<stdio.h>
// #include<stdlib.h>
#define SIZE 10 //tamnanho do BUUFFER CIRCULAR
#define SUCCESS 0
#define FAIL 1
#define REPEAT 2
int start=0;
int end=0;

// ponteiro de funcao
typedef char (*ptrFunc)(void);
//estrutura de cada processo
typedef struct {
    ptrFunc func;
}process;
//BUFFER CIRCULAR
process * pool[];
//funcoes do kernel
char kernelInit(){
    start = 0;
    end = 0;
    //quer dizer que buffer circular do kernel esta vazio, e pode receber processos
    return SUCCESS;
}

char kernelAddProc(process *newPRoc){
    if (((end+1)%SIZE) != start) // se o buffer do kernel esta cheio
    {
        pool[end] = newPRoc; // adiciona na posicao end que e sempre vazia
        end = (end+1)%SIZE;
        return SUCCESS;
    }
    return FAIL;
}

void kernelLoop(){
    for (;;){
        if (start != end) // verifica se ta vazio
        {
            if (pool[start]->func() == REPEAT)//printa o teste e compara se e repeat
            {
                kernelAddProc(pool[start]);
            }
            start = (start+1)%SIZE;
        }
    }
}

char tst1(){printf("process 1 executado\n");return SUCCESS;}
char tst2(){printf("process 2 executado\n");return REPEAT;}
char tst3(){printf("process 3 executado\n");return SUCCESS;}

int main(int argc, char const *argv[])
{
    //passando funcoes teste para os processs
    process p1 = {tst1};
    process p2 = {tst2};
    process p3 = {tst3};

    kernelInit();

    //teste ver se process foi adicionado com sucesso
    if ((kernelAddProc(&p1)) == SUCCESS)
    {
        printf("1st process added \n");
    }
    if ((kernelAddProc(&p2)) == SUCCESS)
    {
        printf("2st process added \n");
    }
    if ((kernelAddProc(&p3)) == SUCCESS)
    {
        printf("3st process added \n");
    }
    
    kernelLoop();

    return 0;
}
