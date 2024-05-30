> Checkout textbook P100 for more info.

We only need to know 2 specified process scheduling algorithm:

- RR (Round Robin)
- MFQ (Multilevel feedback queue)

# Round Robin

Check out [RR Algorithm Exp Simulation](./exp/proc_algo_rr.md) for more info.

Notice that there are two _interrupt streatgy_ on RR algorithm:

- Only interrupt when time slice end.
- Interrupt once task finished.

> Checkout Textbook P100 for more info.

# Multilevel Feedback Queue

This means there are several queue with descending priority in system.

When a new process arrived:

- Put into first queue. (Highest priority)
- Give one time slice
- If not finished, move into the next queue. (Priority reduced)

For CPU:

- Every queue works with RR algorithm.
- Queue with lower priority will have longer time slice.
- **Queue k with be dealt only when [0, k-1] is all empty.**

## Examples

```
<q priority = 99> 
<q priority = 98>
<q priority = 97>

A, B, C arrived

<q priority = 99> A -> B -> C
<q priority = 98>
<q priority = 97>

Time Slice: 1 -> A, not finished, move to next queue

<q priority = 99> B -> C
<q priority = 98> A
<q priority = 97>

Time Slice: 1 -> B, finished

<q priority = 99> C
<q priority = 98> A
<q priority = 97>

Time Slice: 1 -> C, not finished, move to next queue

<q priority = 99>
<q priority = 98> A -> C
<q priority = 97>

Time Slice: 2 -> C, not finished, move to next queue

<q priority = 99>
<q priority = 98> C
<q priority = 97> A

D arrived

<q priority = 99> D
<q priority = 98> 
<q priority = 97> A -> C

Time Slice: 1 -> D, finished

<q priority = 99> 
<q priority = 98> 
<q priority = 97> A -> C

Time Slice: 2 -> A, not finished, no next queue, move to end of the queue (RR)

<q priority = 99> 
<q priority = 98> 
<q priority = 97> C -> AC -> A

Time Slice: 2 -> C, not finished, no next queue, move to end of the queue (RR)

<q priority = 99> 
<q priority = 98> 
<q priority = 97> A -> C

... loop to deal with A and C until finished.
```