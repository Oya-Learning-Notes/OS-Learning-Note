# FCFS Algorithm

FCFS (First-come first-serve) algorithm. This is quite simple, who come first then CPU will first start to process whom.

Consider this process list:

| Process ID         | 1*  | 2  | 3  | 4   |
|--------------------|-----|----|----|-----|
| Arrive Time (min)  | 0   | 50 | 60 | 110 |
| Process Time (min) | 120 | 30 | 6  | 12  |

If we use FCFS to deal with this kind of task, then we will get the result below:

| Process ID         | 1   | 2    | 3   | 4    |
|--------------------|-----|------|-----|------|
| Arrive Time (min)  | 0   | 50   | 60  | 110  |
| Process Time (min) | 120 | 30   | 6   | 12   |
| Start Timestamp    | 0   | 120  | 150 | 156  |
| Finish Timestamp   | 120 | 150  | 156 | 168  |
| Response Time      | 120 | 100  | 96  | 58   |
| Weighted Res Time  | 1   | 3.33 | 16  | 4.83 |

Task running sequence:

```
1 -> 2 -> 3 -> 4
```

# SJF

SJF means Short-job-first. Still if we use the task list above then we get the sequence:

```
1 -> 3 -> 4 -> 2
```

This is because when `1` arrived, there is no active task, so `1` start to run. Then when it finished, `2`, `3` and `4` were all arrived, so SJF pick up the least-process-time task to process.

# PSA (HRRN)

PSA (Priority-scheduleing algorithm) will decide the process sequence based on the _dynamic priority_ .

> After checking, the name of this algorithm could be HRRN(Highest Response Ratio Next), please check textbook for more info.

The priority could be calculated using formula below:

```
priority = (waiting_time + process_time) / process_time
         = 1 + waiting_time / process_time
```

This means when waiting time is equal, the task with shorter process time will have higher priority, this is some kind like SJF, but longer task will gain priority while they keep waiting.

PSA would usually be a better choice compare to FCFS and SJF algorithm.

Still let's consider the first example:

First of all, `1` arrived and no active task, so `1` run first.

| Process ID         | 1   | 2                | 3                      | 4                |
|--------------------|-----|------------------|------------------------|------------------|
| Arrive Time (min)  | 0   | 50               | 60                     | 110              |
| Process Time (min) | 120 | 30               | 6                      | 12               |
| Start Timestamp    | 0   |                  |                        |                  |
| Finish Timestamp   | 120 |                  |                        |                  |
| Response Time      | 120 |                  |                        |                  |
| Weighted Res Time  | 1   |                  |                        |                  |
| Current Wait Time  |     | 70               | 60                     | 10               |
| Priority           |     | 3.33 (1 + 70/30) | 11 (1 + 60/6) Selected | 1.83 (1 + 10/12) |

When `1` finished, we calculate the dynamic priority, and found `3` has highest priority 11, so next process task is 3.

Then when `3` finished, we get:

| Process ID         | 1   | 2                | 3   | 4                |
|--------------------|-----|------------------|-----|------------------|
| Arrive Time (min)  | 0   | 50               | 60  | 110              |
| Process Time (min) | 120 | 30               | 6   | 12               |
| Start Timestamp    | 0   |                  | 120 |                  |
| Finish Timestamp   | 120 |                  | 126 |                  |
| Response Time      | 120 |                  | 66  |                  |
| Weighted Res Time  | 1   |                  | 11  |                  |
| Current Wait Time  |     | 76               |     | 16               |
| Priority           |     | 3.53 (1 + 76/30) |     | 2.33 (1 + 16/12) |

So next task is `2`, and so finally is `4`.

At the end we get:

| Process ID         | 1   | 2    | 3   | 4    |
|--------------------|-----|------|-----|------|
| Arrive Time (min)  | 0   | 50   | 60  | 110  |
| Process Time (min) | 120 | 30   | 6   | 12   |
| Start Timestamp    | 0   | 126  | 120 | 156  |
| Finish Timestamp   | 120 | 156  | 126 | 168  |
| Response Time      | 120 | 106  | 66  | 58   |
| Weighted Res Time  | 1   | 3.53 | 11  | 4.83 |
| Current Wait Time  |     |      |     |      |
| Priority           |     |      |     |      |

> Check out textbook P96 for more info.
