#ifndef PROCESS_H
#define PROCESS_H

#define SUCCESS 0
#define FAIL 1
#define REPEAT 2

#define BUFFER_SIZE 10

#define MIN_INT -30000

typedef void (*PtrFunc)(void);//pomteiro de funcao
typedef char (*NPtrFunc)(int);

typedef struct
{
    int id;
    int priority;
    int time_left;
    int running;
    // PtrFunc func;
    NPtrFunc nfunc;
    int period;
    int start;
} Process;

extern Process processes[BUFFER_SIZE];
extern int num_processes;
extern int current_process;

extern int end;


char create_process(int priority);
void set_process_priority(int id, int priority);
void terminate_process(int id);
void schedule_next_process();
void print_process(Process *p);
void print_processes_list(Process *p);
void exec_process();
char remove_process();
void kernel_clock();
char kernel_add_process(Process* new_proc);
void kernel_loop();


#endif // PROCESS_H