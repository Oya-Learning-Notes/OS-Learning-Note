# Disk Data Access Time

Disk access time could be __divided into 3 parts.__

- Track Searching ($T_s$) 寻道时间
- Rotation Delay ($T_d$) 旋转延迟时间
- Transaction ($T_t$) 传输时间

## Track Searching

The track searching time consists of two part:

- Start-up Time of `head`: $s$
- Time for `head` to move `n` tracks. $n \cdot m$.

Here $m$ is the time for `head` to move for one track. Usually, we have $m = 0.2$ . For some high-performence disk, $m < 0.1$

## Rotation Delay

This part depends on the type of the disk.

## Transaction Time

Consider that:

- Data size is $b$ bytes.
- Disk rotates speed is $r (round/s)$
- Data size in one single round on disk is $N$.

Then we have:

$$
T_t = \frac{b}{r \cdot N}
$$

For scheduling of I/O request, check [Disk I/O Request Scheduling](./disk_schedule_algo.md)