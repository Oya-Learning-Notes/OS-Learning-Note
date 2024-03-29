There are two different types of reader-writer porblem:

- Reader-first (First Reader Writer Model)
- Writer-first (Second Reader Writer Model)

The difference between this two types is that in _reader-first_ mode, while one writer is ready to write, reader could still be possible to access the file. However in _writer-first_ mode, as long as there have a ready writer, reader will not be allowed to access the file.

## Reader-First with Record Semaphore

To solve this problem, we could use _record semaphore_ .

```cpp
semaphore rmutex = 1; // used as mutex of readCount
int readCount = 0; // record count of current active reader
semaphore wmutex = 1; // use as writer lock

void reader(){
    while(true) {
        // increase readCount
        wait(rmutex);
        if(readCount == 0){
            wait(wmutex);
        }
        ++readCount;
        signal(rmutex);
        
        // read operation

        // decrease readCount
        wait(rmutex);
        --readCount;
        if(readCount == 0){
            signal(wmutex);
        }
        signal(rmutex);
    };
}

void writer(){
    while(true){
        wait(wmutex);
        // do write operation
        signal(wmutex);
    }
}
```

The code above implement a _reader-first_ model. Because in this case, even the writer is ready to write, reader still could first reach the resources.

We could consider the **first `reader` takes the responsibility to stop writer to write, and the last `reader` takes the responsiblity to allow `writer` to write**, notice these could be done by different `reader` processes.

# Writer-First with Semaphore Set

```cpp
const int maxActiveReader = 10;

semaphore readerSlotCount = maxActiveReader; // record the rest available count of reader process
semaphore addReaderMutex = 1; // use to control if new reader allowed, used as a switch

void reader(){
    while(true){
        Swait(addReaderMutex, 1, 0);
        Swait(readerSlotCount, 1, 1);
        // do read operation
        Ssignal(readerSlotCount, 1);
    }
}

void writer(){
    while(true){
        Swait(addReaderMutex, 1, 1);
        Swait(readerSlotCount, maxActiveReader, maxActiveReader);
        // do write operation
        Ssignal(readerSlotCount, maxActiveReader);
        Ssignal(addReaderMutex, 1);
    }
}
```

The code implementation above require to specified a max available concurrent reader process.

## Inside Reader Process

In `reader` process, before perform read operation, we first check if new reader process is allowed, this is done by using `Ssignal(addReaderMutex, 1, 0);`, this means when `addReaderMutex>1`, the lock could be acquired, however **this will not cause the semaphore to decrease since the third parameter is `0`**.

## Inside Writer Process

In writer process, `Swait(addReaderMutex, 1, 1)` will first acquired the `addReaderMutex`, however different from the reader process, **this time when the lock is successfully acquired, the count of `addReaderMutex` will decrease to `0`**, and this will cause no more new reader is allowed until writers call signal again. Notice that already existing reader process will still running until they finished.

Then writer process will try to acquire all `readerSlotCount` by using `Swait(readerSlotCount)`, this means only when all currently active reader process finished and return its lock, then the writer will be able to acquired this lock. And during the running of writer process, `readerSlotCount` will remain `0`, means no reader will be allowed when writer is writing.