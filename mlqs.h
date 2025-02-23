typedef struct PCB {
    int pid;
    int priority;  // 0 to 3    // 0 is highest priority
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completed;
}PCB;

#define QUEUE_SIZE 5
#define TIME_QUANTUM 20
#define RR_TIME_QUANTUM 4

int runme();

int inputHandler(PCB process[], int numOfProcesses);

int compareFIFO(const void *a, const void *b);

int queueInitializeSJF(PCB *processes, PCB *queue, int numOfProcesses, int priority);

void printPCB(PCB array[], int iterations);

void PCBinitialization(PCB process[], int numOfProcesses);

int roundRobin(PCB *q0, int queueSize, int *time);

int FIFOnSJF(PCB *queue, int queueSize, int *time);


int compareSJF(const void * a, const void * b);

int queueInitializeFIFO(PCB *processes, PCB *queue, int numOfProcesses, int priority);
