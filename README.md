# Multilevel Queue Scheduling Implementation

## Instructions
- Each queue defines a maximum of 5 processes per queue. If you need more than that, change `#define QUEUE_SIZE 5` to the desired size in `mlqs.h`.
- To run the program, ensure `mlqs.h` and `mlqs.c` are in the same directory.
- Compilation Command: `gcc mlqs.c`
- Execution Command: `./a.out`
- The program is designed to run on UNIX systems.

## Introduction
Multilevel Queue Scheduling is a CPU scheduling algorithm that categorizes processes into multiple queues based on priority. Each queue follows a different scheduling algorithm:
- **Queue 0 (Highest Priority):** Round Robin (RR)
- **Queue 1:** Shortest Job First (SJF)
- **Queue 2:** Shortest Job First (SJF)
- **Queue 3 (Lowest Priority):** First-In-First-Out (FIFO)

The program prompts the user for process details, assigns them to the appropriate queue based on priority, and executes them accordingly.

## Implementation
The program was developed in C, following these steps:
1. **Process Input Handling:**
   - The user enters the number of processes along with Process ID, Arrival Time, Burst Time, and Priority (0-3).
2. **Queue Initialization:**
   - Queue 0 is sorted by arrival time and executed using Round Robin (RR).
   - Queues 1 & 2 are sorted by burst time and executed using Shortest Job First (SJF).
   - Queue 3 is sorted by arrival time and executed using FIFO.
3. **Process Execution:**
   - Each queue is assigned a **20-second time quantum**.
4. **Calculating Performance Metrics:**
   - Waiting Time (WT)
   - Turnaround Time (TAT)

## Results and Analysis
### Pros and Cons of Each Scheduling Algorithm

| Scheduling Algorithm | Pros | Cons |
|----------------------|------|------|
| **Round Robin (Queue 0 - Highest Priority)** | Ensures fairness as all processes get CPU time. Reduces starvation issues. | High context switching overhead. May lead to longer turnaround time for shorter processes. |
| **Shortest Job First (Queues 1 & 2)** | Minimizes waiting and turnaround time for shorter processes. | Starvation risk for longer processes if short jobs keep arriving. Requires knowledge of burst time in advance. |
| **First-In-First-Out (Queue 3 - Lowest Priority)** | Simple and easy to implement. No overhead from context switching. Efficient for batch processing. | Processes with long burst times delay execution of subsequent processes. Not suitable for time-sharing environments. |

## Conclusion and Limitations
The Multilevel Queue Scheduling program effectively demonstrates how different scheduling algorithms handle processes based on priority. However, it has some limitations:
- **Fixed time quantum:** The 20-second quantum may not be optimal for all workloads.
- **SJF starvation issue:** Long processes in SJF queues may suffer indefinite delays.

### Future Improvements
Future enhancements could include:
- **Dynamic Priority Adjustment:** To adapt process priority dynamically.
- **Aging Mechanisms:** To mitigate starvation issues in SJF queues.

This implementation provides insight into how different scheduling algorithms perform under a priority-based queueing system, showcasing their strengths and limitations.

