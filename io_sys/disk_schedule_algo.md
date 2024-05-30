# Overview

- **FCFS**
- **SSFT**
- **SCAN** (Solve Starvation)
    - **CSCAN** (Improved version of `SCAN`, considering moving direction)
- **NStepSCAN** (Solve Stickness)
    - **FSCAN** (Simple version of `NStepSCAN`, reduce sequence number to `2`)

# FCFS

__First Come First Serve__. As it's name implies, First come, first serves.

# SSFT

__Short Search Time First__ algorithm. Always goto the tracks that __clostest to current `head` position__.

# SCAN

`SSFT` is a great scheduling algorithm and has been widely use. But it will have a chance to cause __Stravation__.

## Stravation

> Starvation means there is a large amount of request come in that all close to the `head`, then the ones far away from `head` will never be proceed for a long time, stravation occurred.

## Algorithm Detail

To solve _Stravation_ problem, __`SCAN` not only consider the distance to `head`, but also consider the _Moving Direction_.__

For example `head` were in `90`, now moved to `100`. Now we have two candidate: `120`, `130`, `90`. Although `90` is closer to `head`, but it's not concur with current moving direction of `head`. So we would choose `120` as the next target.

> This method are also called _Elevation Algorithm_.

# CSCAN

This method is __similar to `SCAN` but limit the direction of `head`__.

In `SCAN` the `head` actually move back and forth. But __in `CSCAN`, for example it could only goes from lower track to greater track. When finished the maximum track request, it immediately go back to the minimum one.__ Or you could think that the maximum track request linked to the minimum one, forming a _Cricle_. That's why this algorithm called circle scan.

# NStepSCAN

## Head Stickness

_Head Stickness_ (Or _Armstickness_, 磁臂粘着) means that when OS are keep requesting some _Hot Tracks_, so the `head` most of time stay at these _Hot Tracks_.

## Algorithm Detail

To solve _Stickness_, __`NStepSCAN` divide the request to several sequence with size `N`__.

- In _Sequence_ level, we use `FCFS`.
- Inside _Sequence_, we use `SCAN` on requests inside the same sequence.

# FSCAN

A simple version of `NStepSCAN`. Only have two sequence.

- Working Sequence: All __current I/O request.__
- Waiting Sequence: All requests __comes in when deal with _Working Sequence_.__

> _Working Sequence_ and _Waiting Sequence_ are not standard name provided by Textbook.