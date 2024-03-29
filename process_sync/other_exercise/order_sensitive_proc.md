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
    wait(p3ReadFin, 1, 0);
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