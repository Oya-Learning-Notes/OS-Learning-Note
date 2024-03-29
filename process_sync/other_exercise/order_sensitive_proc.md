# Problem Description

![image.png](https://s2.loli.net/2024/03/29/qFKi5rMNWXw6fRm.png)

There are 3 company parallel processes `P1` `P2` and `P3`. They get input from a same input device which only allow one process to read at a time (that is, this input device should be considered critical resource). 

Input must be in order, and `P1` is responsible to read `a` from device, `P2` is responsible to read `b` from device etc.

# Code Implementation

```cpp
// record the reading status of processes
semaphore p1ReadFin = 0;
semaphore p2ReadFin = 0;
semaphore p3ReadFin = 0;

// record if value of y already been calculated
semaphore yCalcuFin = 0;

// record the number of finished calculation
semaphore calcuFinCount = 0;

DataType a, b, c;
DataType x, y, z;

void p1(){
    // read
    a = readFromInput();
    signal(p1ReadFin);

    // calculate
    wait(p2ReadFin, 1, 0);
    x = a + b;
    signal(calcuFinCount, 1);

    // print
    wait(calcuFinCount, 3, 0);
    printResult(x, y, z);
}

void p2(){
    // read
    wait(p1ReadFin, 1, 0);
    b = readFromInput();
    signal(p2ReadFin);

    // calculate
    wait(p2ReadFin, 1, 0);
    y = a * b;
    signal(calcuFinCount, 1);
    signal(yCalcuFin);
}

void p3(){
    // read
    wait(p2ReadFin, 1, 0);
    c = readFromInput();
    signal(p3ReadFin);

    // calculate
    wait(yCalcuFin, 1, 0);
    wait(p3ReadFin, 1, 0);
    z = y + c - a;
    signal(calcuFinCount, 1);
}
```

Actually I think this problem is quite like the problem of using semaphore to solve process dependency problem.

First let draw out the original dependency flow chart of this problem:

![image](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/f9b8e00b-d474-4b0b-8dc0-2daf039e0917)

Then we could find some dependency is unnecessary as the green line below:

![image](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/f143c224-c2ae-44b7-9dd6-13ba33afbaf3)

Finally we just need to use semaphore to implement this process sequence control:

![image](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/16cd558e-cf75-4d99-9f72-4f9d68f35869)

As you see at the diagram above, something that worth talk about is:

- `P1 Calc` and `P2 Calc` actually only depend on `P2 Read` is finished. Since `P2 Read` finished must mean that both `a` and `b` are read.
- `P3 Calc` not only depend of `P3 Read` (at this time all input operations are finished, means both `a`, `b`, `c` are available) but also depend on `P2 Calc`, this is because the calculation of `z` depend on the value of `y` which will only available after `P2 Calc` finished.

## About The Implementation

In the implementation we use a lot of _switch_ schema for semaphore waiting. That is `wait(S, t, 0)`, this means when `S > t` then the switch is open and operation is allowed, but the value of `S` will remain and won't be decreased.

Also, the implementation above is **based on the assumptions that those variable `a`, `b`, `c` is not critical towards reading operation**, means more than one processes reading this variable at the same time is acceptable. If not then the implementation need to be modified to protect there is only one process reading the variable at the same time.