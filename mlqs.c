#include <stdio.h>
#include <stdlib.h>
#include "mlqs.h"

int main() {
    runme();
    return 0;
}

int runme() {
    // Get number of processes from the user
    int numOfProcesses;
    printf("Enter the number of processes: ");
    scanf("%d", &numOfProcesses);

    // Create an array of PCBs
    PCB process[numOfProcesses];
    // General PCB initialization
    PCBinitialization(process, numOfProcesses);

    // Initialize the PCBs according to the user input
    inputHandler(process, numOfProcesses);

    // Print the PCBs
    printf("The processes are: \n");
    printPCB(process, numOfProcesses);    

    // Queues for each priority
    PCB q0[QUEUE_SIZE]={0}; // Round Robin
    PCB q1[QUEUE_SIZE]={0}; // SJF
    PCB q2[QUEUE_SIZE]={0}; // SJF
    PCB q3[QUEUE_SIZE]={0}; // FIFO

    // Initialize the queues
    int q0Size = queueInitializeFIFO(process, q0, numOfProcesses, 0);
    int q1Size = queueInitializeSJF(process, q1, numOfProcesses, 1);
    int q2Size = queueInitializeSJF(process, q2, numOfProcesses, 2);
    int q3Size = queueInitializeFIFO(process, q3, numOfProcesses, 3);

    // Print the initialized queues
    printf("\nQ0: \n");printPCB(q0, QUEUE_SIZE);
    printf("Q1: \n");printPCB(q1, QUEUE_SIZE);
    printf("Q2: \n");printPCB(q2, QUEUE_SIZE);
    printf("Q3: \n");printPCB(q3, QUEUE_SIZE);

    // Variables to track completion
    int completedQ0 = 0, completedQ1 = 0, completedQ2 = 0, completedQ3 = 0;
    int time = 0;

    // Simulate CPU switching between queues
    while (completedQ0 < q0Size || completedQ1 < q1Size || completedQ2 < q2Size || completedQ3 < q3Size) {
        int executed = 0;  // Track if any process runs

        // Round Robin for q0
        if (completedQ0 < q0Size) {
            int before = completedQ0;
            completedQ0 += roundRobin(q0, q0Size, &time);
            if (completedQ0 > before) executed = 1;
        }

        // SJF for q1
        if (completedQ1 < q1Size) {
            int before = completedQ1;
            completedQ1 += FIFOnSJF(q1, q1Size, &time);
            if (completedQ1 > before) executed = 1;
        }

        // SJF for q2
        if (completedQ2 < q2Size) {
            int before = completedQ2;
            completedQ2 += FIFOnSJF(q2, q2Size, &time);
            if (completedQ2 > before) executed = 1;
        }

        // FIFO for q3
        if (completedQ3 < q3Size) {
            int before = completedQ3;
            completedQ3 += FIFOnSJF(q3, q3Size, &time);
            if (completedQ3 > before) executed = 1;
        }

        if (!executed) {
            time++;  // Prevent infinite loop if no queue executed
        }
    }

    // Print the final queues
    printf("\nQ0: \n");printPCB(q0, QUEUE_SIZE);
    printf("Q1: \n");printPCB(q1, QUEUE_SIZE);
    printf("Q2: \n");printPCB(q2, QUEUE_SIZE);
    printf("Q3: \n");printPCB(q3, QUEUE_SIZE);

    // completed processes
    if (completedQ0 == q0Size){
        printf("Q0 (RR) Completed\n");
    }
    if (completedQ1 == q1Size){
        printf("Q1 (SJF) Completed\n");
    }
    if (completedQ2 == q2Size){
        printf("Q2 (SJF) Completed\n");
    }
    if (completedQ3 == q3Size){
        printf("Q3 (FIFO) Completed\n");
    }

    return 0;
}


int inputHandler(PCB process[], int numOfProcesses) {
    for (int i = 0; i < numOfProcesses; i++)
    {
        printf("Process %d\n", i+1);

        printf("Enter the process id: ");
        scanf("%d", &process[i].pid);

        printf("Enter the arrival time: ");
        scanf("%d", &process[i].arrival_time);

        printf("Enter the burst time: ");
        scanf("%d", &process[i].burst_time);
        process[i].remaining_time = process[i].burst_time;

        printf("Enter the priority(0 to 3): ");
        scanf("%d", &process[i].priority);

        if (process[i].priority < 0 || process[i].priority > 3)
        {
            printf("Invalid priority: Enter Again->1 , Exit->-1\n");
            int decision;
            scanf("%d", &decision);
            switch (decision)
            {
            case -1:
                return 0;
                break;
            case 1:
                i--;
                break;
            
            default:
                printf("Invalid Input\n");
                continue;
            }
        }

    }
    printf("All Inputs Are Stored Successfuly\n");
    return 0;
}

int compareFIFO(const void *a, const void *b) {
    return ((PCB*)a)->arrival_time - ((PCB*)b)->arrival_time;
}

int compareSJF(const void *a, const void *b) {
    return ((PCB*)a)->burst_time - ((PCB*)b)->burst_time;
}

int queueInitializeFIFO(PCB* processes , PCB* queue ,int numOfProcesses,int priority){
    // sort the processes based on priority
    qsort(processes, numOfProcesses, sizeof(PCB), compareFIFO);

    int index = 0;

    for (int i = 0; i < numOfProcesses; i++)
    {
        if(processes[i].priority == priority){
            queue[index] = processes[i];
            index++;
        }
    }

    printf("Q%d Initialization Successful\n",priority);
    return index;
    
}

int queueInitializeSJF(PCB* processes , PCB* queue, int numOfProcesses, int priority){
    // sort the processes based on SJF
    qsort(processes, numOfProcesses, sizeof(PCB), compareSJF);

    int index = 0;

    for (int i = 0; i < numOfProcesses; i++)
    {
        if(processes[i].priority == priority){
            queue[index] = processes[i];
            index++;
        }
    }

    printf("Q%d Initialization Successful\n",priority);
    return index;
    
}

void printPCB(PCB array[], int iterations){
    printf("PID\tP\tAT\tBT\tWT\tTT\tRT\tC\n");
    for (int i = 0; i < iterations; i++)
    {
        printf("|%d\t", array[i].pid);
        printf("|%d\t", array[i].priority);
        printf("|%d\t", array[i].arrival_time);
        printf("|%d\t", array[i].burst_time);
        printf("|%d\t", array[i].waiting_time);
        printf("|%d\t", array[i].turnaround_time);
        printf("|%d\t", array[i].remaining_time);
        printf("|%d\n", array[i].completed);
    }
    printf("\n");
}

void PCBinitialization(PCB process[] , int numOfProcesses){
    for (int i = 0; i < numOfProcesses; i++)
    {
        process[i].pid = 0;
        process[i].priority = 0;
        process[i].arrival_time = 0;
        process[i].burst_time = 0;
        process[i].waiting_time = 0;
        process[i].turnaround_time = 0;
        process[i].remaining_time = 0;
        process[i].completed = 0;
    }
}

int roundRobin(PCB* q0, int queueSize, int* time) {
    int completed = 0;
    int executed = 0;

    for (int i = 0; i < queueSize; i++) {
        if (q0[i].completed == 0 && q0[i].arrival_time <= *time) {
            if (q0[i].remaining_time > RR_TIME_QUANTUM) {
                // Process can't be completed in one time quantum
                *time += RR_TIME_QUANTUM;
                q0[i].remaining_time -= RR_TIME_QUANTUM;
            } else {
                // Process can be completed in one time quantum
                *time += q0[i].remaining_time;
                q0[i].turnaround_time = *time - q0[i].arrival_time;
                q0[i].waiting_time = q0[i].turnaround_time - q0[i].burst_time;
                q0[i].remaining_time = 0;
                q0[i].completed = 1;
                completed++;
            }
            executed = 1;
        }
    }

    return completed;
}

int FIFOnSJF(PCB* queue, int queueSize, int* time) {
    int completed = 0;
    int executed = 0;

    for (int i = 0; i < queueSize; i++) {
        if (queue[i].completed == 0 && queue[i].arrival_time <= *time) {
            *time += queue[i].burst_time;
            queue[i].turnaround_time = *time - queue[i].arrival_time;
            queue[i].waiting_time = queue[i].turnaround_time - queue[i].burst_time;
            queue[i].remaining_time = 0;
            queue[i].completed = 1;
            completed++;
            executed = 1;
        }
    }

    return completed;
}


