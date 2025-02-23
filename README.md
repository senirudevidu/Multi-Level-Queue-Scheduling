Multilevel Queue Scheduling 
Implementation Report 
Index Number: 23001879 
Reg. Number: 2023/CS/187 
Name: Seniru D.S Seneweera 
0. Instructions: 
·    
·    
·    
·    
·    
Each queue defines a maximum of 5 processes per queue. If need more that that change #define 
QUEUE_SIZE 5  to size that you want.(check mlqs.h) 
To run the program mlqs.h and mlqs.c both files should be in the same directory. 
Compilation Command: gcc mlqs.c 
To run: ./a.out 
Commands work only in UNIX systems. 
1.     Introduction 
Multilevel Queue Scheduling is a CPU scheduling algorithm that categorizes processes into multiple 
queues based on priority. Each queue follows a different scheduling algorithm to handle its processes 
efficiently. 
● Queue 0 (Highest Priority): Round Robin (RR) 
● Queue 1: Shortest Job First (SJF) 
● Queue 2: Shortest Job First (SJF) 
● Queue 3 (Lowest Priority): First-In-First-Out (FIFO) 
The program prompts the user for process details, assigns them to the appropriate queue based on priority, 
and executes them accordingly. 
2. Implementation 
The program was developed in C, following these steps: 
1. Process Input Handling: 
○ The user enters the number of processes along with Process ID, Arrival Time, Burst 
Time, and Priority (0-3). 
2. Queue Initialization: 
○ Queue 0 is sorted by arrival time and executed using Round Robin (RR). 
○ Queues 1 & 2 are sorted by burst time and executed using Shortest Job First (SJF). 
○  Queue 3 is sorted by arrival time and executed using FIFO. 
3. Process Execution: 
○ Each queue is assigned a 20-second time quantum.. 
4. Calculating Performance Metrics: 
○ Waiting Time (WT) 
○ Turnaround Time (TAT) 
3. Results and Analysis 
Pros and Cons of Each Scheduling Algorithm 
Scheduling Algorithm Pros 
Round Robin 
(Queue 0 - Highest 
Priority) 
Shortest Job First 
(Queues 1 & 2) 
First-In-First-Out 
(Queue 3 - Lowest 
Priority) 
Ensures fairness as all processes 
get CPU time. 
Reduces starvation issues. 
Minimizes waiting and 
turnaround time for shorter 
processes.  
Efficient for batch processing. 
Cons 
High context switching overhead.  
May lead to longer turnaround time for 
shorter processes. 
Starvation risk for longer processes if 
short jobs keep arriving. 
Requires knowledge of burst time in 
advance. 
Simple and easy to implement. 
No overhead from context 
switching. 
4. Conclusion and Limitations 
Processes with long burst times delay 
execution of subsequent processes.  
Not suitable for time-sharing 
environments. 
The Multilevel Queue Scheduling program effectively demonstrates how different scheduling algorithms 
handle processes based on priority. The approach balances Here are some limitations: 
● Fixed time quantum: The 20-second may not be optimal for all workloads. 
● SJF starvation issue: Long processes in SJF queues may suffer indefinite delays. 
Future improvements could include Dynamic Priority Adjustment and Aging Mechanisms to mitigate 
starvation issues. 
