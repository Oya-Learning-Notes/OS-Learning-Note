There are several types of scheduling task inside system.

- Job Schedule Algorithm ([Note Link](./process_schedule_algo.md))
- Process Schedule Algorithm
- Realtime Task Schedule Algorithm

**Job Schedule Algorithm:** This part is responsible to choose a job/task from storage and load it to memory. (Usually after it has been loaded to memory, we consider it in the ready list and could be selected and scheduled by Process Schedule Algorithm)

**Process Schedule Algorithm:** This part is responsible to choose the processes in the ready list to run on the CPU.

**Realtime Task Schedule Algorithm:** This is a part of _Process Scheduling System_ since _realtime task_ is a special type of process that has stricter limitation.
