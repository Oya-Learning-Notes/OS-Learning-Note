# Infinite Producer / Consumer Problem

Consider we have a queue of infinite size.

```cpp
element repo[]; // this is an infinite array
int in = 0;
semaphore inMutex = 1;
int out = 0;
semaphore outMutex = 1;
semaphore productCount=0;

void producer(){
    while(true){
        // pre-produce in here, assume that produce() is expensive work
        auto product = produce();

        // put into repo
        wait(inMutex);
        repo[in] = product;
        in++;
        signal(inMutex);
        signal(productCount);
    }
}

void consumer(){
    while(true){
        auto product = emptyProduct();

        // retrive product
        wait(productCount);
        wait(outMutex);
        product = repo[out];
        ++out;
        signal(outMutex);
        
        // consume
        consume(product);
    }
}
```

This is actually simpler than the original PC model because `producer` process now have no limitation at all.

# Refs

[More Exercises - PC Model with Different Product And Limitation](./other_exercise/pc_with_limit.md)