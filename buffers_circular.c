#include <stdio.h>
#define BUFFERSIZE 10
int start = 0, end = 0;
typedef void (*ptrFunc)(void);//ponteiro de funcao

typedef struct{
    char name;
    int time;
    ptrFunc func;
} process;

process buffer[BUFFERSIZE];

void add(process *nname, int ntime, ptrFunc fpointer)
{
    if ((end + 1) % BUFFERSIZE != start){ // verifica se lista ta cheia
        buffer[end].name = nname;
        buffer[end].time = ntime;
        buffer[end].func = fpointer;
        end = (end + 1) % BUFFERSIZE;
    }
}

void remover()
{
    if (start != end)//lista 
    {
        start = (start + 1) % BUFFERSIZE;
    }
}

void exec()
{
    if (start != end)// lista vazia
    {
        buffer[start].func();
    }
}

void func1() { printf("f1 \n"); }
void func2() { printf("f2 \n"); }
void func3() { printf("f3 \n"); }

int main(int argc, char const *argv[])
{
    add("Proc1", 1, func1);
    add("Proc2", 2, func2);
    add("Proc3", 3, func3);
    exec();
    exec();
    exec();
    remover();
    exec();
    remover();
    exec();
    remover();
}
