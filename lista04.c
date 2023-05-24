#include <stdio.h>
#define MAX 10

int main()
{

    long int matricula[max], aux;
    int i = 1, j = 0;

    while (i <= 10)
    {

        printf("digite matricula[%d]: ", i);
        scanf("%ld", matricula[i]);
        aux = matricula[i];

        while (true)
        {
            if (aux == matricula[j])
            {
                j--;
                printf("digite matricula[%d]: ", i);
                scanf("%ld", matricula[i]);
            }else{
                j++;
                if (j == MAX)
                {
                    break;
                }
                
            }
        }
    }
}