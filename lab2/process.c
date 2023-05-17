#include "process.h"

#include <stdio.h>

Process processes[BUFFER_SIZE];
int num_processes = 0;
int current_process = 0;
int end = 0;


char print_myself(int n)
{
    printf("My ID: %d\n", n);
    return SUCCESS;
}

char create_process(int priority)
{
    if(((end + 1) % BUFFER_SIZE) != current_process)
    {
        Process p = {priority, priority, 10, 0, print_myself, 5, 0};
        // p.nfunc = print_myself;
        processes[end] = p;
        end = (end + 1) % BUFFER_SIZE;
        return SUCCESS;
    }
    else
    {
        printf("FAILED to create process.\n");
    }

    return FAIL;
}

void set_process_priority(int id, int priority)
{
    int aux = current_process;
    while(aux != end)
    {
        if(processes[aux].id == id)
        {
            processes[aux].priority = priority;
            return;
        }

        aux = (aux + 1) % BUFFER_SIZE;
    }

    printf("Process not found.\n");
}

void terminate_process(int id)
{
    int aux = current_process;
    while(aux != end)
    {
        if(processes[aux].id == id)
        {
            printf("TODO: Terminate process\n");
            return;
        }

        aux = (aux + 1) % BUFFER_SIZE;
    }

    printf("Process not found.\n");
}

void schedule_next_process()
{
    int next = -1;
    
    if(current_process != end)
    {
        // Fint the process with the lowest timer
        next = current_process;
        int j = (current_process + 1) % BUFFER_SIZE;

        while(j != end)
        {
            if(processes[j].time_left < processes[next].time_left)
                next = j;
        
            j = (j + 1) % BUFFER_SIZE;
        }

        // Change processes positions
        Process* aux = &processes[next];
        processes[next] = processes[current_process];
        processes[current_process] = *aux;

        // Increment current_process position
        current_process = (current_process + 1) % BUFFER_SIZE;
    }
}

void print_process(Process *p)
{
    printf("Process:\n           \
            \tid: %d\n           \
            \tpriority: %d\n     \
            \ttime_left: %d\n    \
            \trunning: %d\n",
            p->id, p->priority, p->time_left, p->running);
}

void print_processes_list(Process *p)
{
    for(int i = 0; i < end; i++)
    {
        print_process(&p[i]);
        printf("\n");
    }
}

void exec_process()
{
    if(current_process != end)
    {
        processes[current_process].nfunc(processes[current_process].id);
        current_process = (current_process + 1) % BUFFER_SIZE;
    }
}

char remove_process()
{
    current_process = (current_process + 1) % BUFFER_SIZE;
}

void kernel_clock()
{
    unsigned char i = current_process;
    for(unsigned char i = current_process; i != end; i = (i + 1 % BUFFER_SIZE))
    {
        if(processes[i].start > MIN_INT)
            processes[i].start--;
    }
}

char kernel_add_process(Process* new_proc)
{
    if(((end + 1) % BUFFER_SIZE) != current_process)
    {
        processes[end] = *new_proc;
        processes[end].start += new_proc->period;
        end = (end + 1) % BUFFER_SIZE;
        return SUCCESS;
    }

    return FAIL;
}

void kernel_loop()
{
    int n = 0;
    for(;;)
    {
        printf("cur = %d and end = %d\n", current_process, end);
        if(current_process < end)
        {
            if(processes[current_process].nfunc(processes[current_process].id) == REPEAT)
                kernel_add_process(&processes[current_process]);
        }

        current_process = (current_process + 1) % BUFFER_SIZE;
        
        n++;
        if(n == 20)
            break;
    }
}