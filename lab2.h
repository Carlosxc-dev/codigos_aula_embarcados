#ifndef LAB2_H
#define LAB2_H

#define SUCESS 0
#define FAIL 1
#define BUFFERSIZE 10

typedef struct {
    int id;
    int priority;
    int time_left;
    int running;
} Process;

Process processes[BUFFERSIZE];
int num_processes = 0;
int current_process = -1;
int end_process = 0;

void print();
char create_process(void* data);
void set_priority(int id, int priority);
void schedule_next_process();
void terminate_process();

#endif