#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int **ptr = (int **)malloc(10 * sizeof(int *));//linhas

    for (int i = 0; i < 10; i++){
        ptr[i] = (int *)malloc(10 * sizeof(int));//colunas
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ptr[i][j] = 10;
            printf("%d ", ptr[i][j]);
        }
        printf("\n");
    }
    free(ptr);
    return 0;
}
