# Bridge Problem

In this problem the bridge has a max capacity of 2 people in the middle of the bridge, but both the south and north entry could only pass one person at a time.

```cpp
semaphore southGateMutex = 1;
semaphore northGateMutex = 1;
semaphore maxOnBridgeCount = 2;

void southToNorth(){
    while(true){
        // make sure bridge still capable
        wait(maxOnBridgeCount);

        // try go on bridge
        wait(southGateMutex);
        goOnBridge();
        signal(southGateMutex);

        doSthOnBridge();
        rest();

        // try to leave bridge at north
        wait(northGateMutex);
        goOffBridge();
        signal(northGateMutex);

        // leave bridge, release bridge capable resource
        signal(maxOnBridgeCount);
    }
}

void northToSouth(){
    while(true){
        // make sure bridge still capable
        wait(maxOnBridgeCount);

        // try go on bridge
        wait(northGateMutex);
        goOnBridge();
        signal(northGateMutex);

        doSthOnBridge();
        rest();

        // try to leave bridge at north
        wait(southGateMutex);
        goOffBridge();
        signal(southGateMutex);

        // leave bridge, release bridge capable resource
        signal(maxOnBridgeCount);
    }
}
```

Notice that **bridge capability check must always be done first and capability release must be at last**. If we first **wait the gate lock before check bridge ability, then there will be a chance for deadlock to occur**.

Consider there is already 2 people on bridge, and two gates are locked by the people who want to go to the bridge. Then in this case:

- All the people want to go to the bridge won't success, because `maxOnBridgeCount` is already `0`.
- All the people on bridge could get off since both gate lock are busy now.

Then the deadlock occurred.

# Management Process

We could also try using management process to handle this model:

```cpp
class semaphore;
class Pastport;

// Bridge class
class Bridge
{
private:
    semaphore mCapacity;
    semaphore nMutex = 1;
    semaphore sMutex = 1;

public:
    Bridge(semaphore capacity);

    void goToSouth(const People &p);
    void goToNorth(People p);
};

// initialize management process
Bridge::Bridge(semaphore capacity) : mCapacity(capacity) {}

void Bridge::goToNorth(const People &p)
{
    wait(mCapacity);

    wait(sMutex);
    upBridgeFromSouth(p);
    signal(sMutex);

    p.doSomethingOnBridge();

    wait(nMutex);
    leaveBridgeFromNorth(p);
    signal(nMutex);

    signal(mCapacity);
}

void Bridge::goToSouth(const People &p)
{
    wait(mCapacity);

    wait(nMutex);
    upBridgeFromSouth(p);
    signal(nMutex);

    p.doSomethingOnBridge();

    wait(sMutex);
    leaveBridgeFromNorth(p);
    signal(sMutex);

    signal(mCapacity);
}

Bridge bridge{2}; // create manage process instance with capacity 2

void peopleGoSouth()
{
    while (true)
    {
        People p{};
        bridge.goToSouth(p);
    }
}

void peopleGoNorth()
{
    while (true)
    {
        People p{};
        bridge.goToNorth(p);
    }
}
```

In the example above, the management of the critical resource `Bridge` has been capsulated into a management class. When people want to 