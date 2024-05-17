# Contents

- Job Schedule Algorithm [Note Link](./job_schedule_algo.md)
- Process Schedule Algorithm [Note Link](./proc_schedule.md)
- Realtime Task Schedule Algorithm [Note Link](./realtime_schedule.md)

![IMG_2142](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/206b5fdc-27c3-4e70-a3f3-0297ebf0c3a4)

The image above shows the relationships between algorithms and their category.

# Diffrence between them

**Job Schedule Algorithm:** 

This part is responsible to **choose a job/task from storage and load it to memory.** (Usually after it has been loaded to memory, we consider it in the ready list and could be selected and scheduled by *Process Schedule Algorithm*)

- FCFS
- SJF
- HRRN(PSA)

**Process Schedule Algorithm:** This part is responsible to **choose the processes in the ready list to run on the CPU**.

- RR (Round Robin)

**Realtime Task Schedule Algorithm:** This is a part of _Process Scheduling System_ since _realtime task_ is a special type of process that has stricter limitation.

- EDF (Earliest Deadline First)
- LLF (Least Laxity First)
