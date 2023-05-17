#include <stdio.h>
#include "process.h"

char my_print(int n)
{
    printf("My ID: %d\n", n);
    return SUCCESS;
}

int main(int argc, char** argv)
{
    int id = 0;
    Process p0 = {id, id++, 10, 0, my_print, 5, 0};
    Process p1 = {id, id++, 10, 0, my_print, 5, 0};
    Process p2 = {id, id++, 10, 0, my_print, 5, 0};
    Process p3 = {id, id++, 10, 0, my_print, 5, 0};
    Process p4 = {id, id++, 10, 0, my_print, 5, 0};

    if(kernel_add_process(&p0) == FAIL)
        printf("Failed to add process %d.\n", p0.id);
    if(kernel_add_process(&p1) == FAIL)
        printf("Failed to add process %d.\n", p1.id);
    if(kernel_add_process(&p2) == FAIL)
        printf("Failed to add process %d.\n", p2.id);
    if(kernel_add_process(&p3) == FAIL)
        printf("Failed to add process %d.\n", p3.id);
    if(kernel_add_process(&p4) == FAIL)
        printf("Failed to add process %d.\n", p4.id);

    kernel_loop();

    printf("Hello, Kernel!\n");
    return 0;
}