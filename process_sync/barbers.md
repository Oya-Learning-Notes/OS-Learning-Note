Here is an implementation to solve barber's shop problem.

```cpp
const int maxChair = 10;

int waiting = 0; // record the current number of people waiting for barber
semaphore waitingMutex = 1; // mutex to protect waiting variable
semaphore customers = 0; // actually store the same info as waiting

void barber(){
    while(true){
        wait(customers);
        wait(waitingMutex);
        --waiting;
        signal(waitingMutex);
        
        doHairCut();
    }
}

void customer(){
    while(true){
        wait(waitingMutex);
        if(waiting >= maxChair){
            // here remember to release the lock
            signal(waitingMutex);
            continue; // here means this customer leave the barber's shop
        }
        ++waiting;
        signal(waitingMutex);
        signal(customers);
    }
}
```

# Multiple Barbers

Now let's consider a more complexed scenario:

- There are **more than one barbers** in the barber shop.
- Customer could appoint for a specific barber.

```cpp
const int barbersCount = 3;
const int maxWaiting = 10;

int totalWaiting = 0;                           // store the total waiting number
semaphore wMutex = maxWaiting;                  // protect totalWaiting variable
semaphore barbersCustomers[barbersCount] = {0}; // all initialized to 0
semaphore barbersAvailable[barbersCount];       // all initailized to 1
std::fill(barbersAvailable, barbersAvailable + barbersCount, 1);

// Barbers process (need to provide zero-indexed barber number)
void barbers(int barberIndex)
{
    while (true)
    {
        // first make sure this barber is free now
        wait(barbersAvailable[barberIndex]);

        wait(barbersCustomers[barberIndex]); // if there has customers appointed to this barber, start working
        wait(wMutex);
        --totalWaiting;
        signal(wMutex);

        startHairCut();

        signal(barbersAvailable[barberIndex]);
    }
}

void customers(int barberIndex)
{
    while(true){
        wait(wMutex);
        if (totalWaiting >= maxWaiting)
        {
            // leave barber shop
            signal(wMutex);
            continue;
        }
        ++totalWaiting;
        signal(barbersCustomers[barberIndex]); // wake the corresponding barber
        signal(wMutex);

        findAndTakeSeat();
    }
}

int main()
{
    cobegin for (int i = 0; i < barbersCount; ++i)
    {
        barbers(i);
        customers(i);
    }
    coend
}
```

The above example didn't handle the logic of the barbers finding it's customer, it actually only guarantee the number relationship of the barbers and customers is correct.