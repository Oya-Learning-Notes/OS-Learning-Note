There are several types of scheduling task inside system.

- Job Schedule Algorithm [Note Link](./job_schedule_algo.md)
- Process Schedule Algorithm [Note Link](./process_schedule_algo.md)
- Realtime Task Schedule Algorithm [Note Link](./realtime_schedule.md)

**Job Schedule Algorithm:** 

This part is responsible to choose a job/task from storage and load it to memory. (Usually after it has been loaded to memory, we consider it in the ready list and could be selected and scheduled by Process Schedule Algorithm)

- FCFS
- SJF
- HRRN(PSA)

**Process Schedule Algorithm:** This part is responsible to choose the processes in the ready list to run on the CPU.

- RR (Round Robin)

**Realtime Task Schedule Algorithm:** This is a part of _Process Scheduling System_ since _realtime task_ is a special type of process that has stricter limitation.

- EDF (Earliest Deadline First)
- LLF (Least Laxity First)