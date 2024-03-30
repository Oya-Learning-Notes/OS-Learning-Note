# Problem Description

First if you don't know _Producer Consumer Model_, please check the basic version of the model first.

This model is based on the producer consumer model. Assume there are two different producer produce two different type of product `A` and `B`.

They share the same repository, denote the number of product A in the repository is P and the number of product B in repo is Q, then there are following limit.

- Repository has max capacity `N`.
- At anytime, `P - Q <= X`, `Q - P <= Y`

# Code Implementation

```cpp
// initial config for this problem
const int x;
const int y;
const int n;

semaphore emptyA = x;    // record how many `A` could still be added to repo without breaking the rules.
semaphore emptyB = y;    // similar to `emptyA`
semaphore emptyRepo = n; // record how many empty space inside repository
semaphore fullRepo = 0;  // record how many products are in the repository

Product buf[n];
int in = 0, out = 0;
semaphore inMutex = 1, outMutex = 1;



void producerA(){
    // produce the product first
    Product product = produceA();

    // acquire resources
    wait(emptyA);
    wait(emptyRepo);

    // put product into repo
    wait(inMutex);
    buf[in] = product;
    ++inMutex;
    inMutex %= n;
    signal(inMutex);

    // for me I think the order of release lock doesn't matter
    signal(emptyB);
    signal(fullRepo);
}

// producerB process code is similar so I won't list it here

void consumer(){
    Product product;

    // take out a product from buffer (repo)
    wait(fullRepo);
    wait(outMutex);
    product = buf[out];
    ++out;
    outMutex %= n;
    signal(outMutex);
    signal(emptyRepo);

    // consume product
    consume(product);
}
```

## Usage of emptyA / emptyB

Semaphore `emptyA` and `emptyB` is used to protect the producer to follow the second limitation in the problem, that is max difference of different type of products should be limited. If you need to add an `A`, decrease emptyA which means you are using up the capacity of `A` in the repo, so we should call `wait(emptyA)`, in the meanwhile since you add `A`, means limitation of the max number of `B` in the repo is loosen, so we should call `signal(emptyB)`.

## Lock Acquire Sequence Inside Producer

Also notice that inside `producerA()` we first acquire `emptyA` then acquire `emptyRepo`. **This order could NOT be changed otherwise there will be a chance for deadlock.**

Assume we first acquire `emptyRepo` before acquire `emptyA`. Consider this situation when `emptyA` already `0`, means max number of `A` in the repo is reached, and `emptyRepo = 1`, means there is a last empty space inside repo. However if at this moment a `producerA` acuqired the `emptyRepo`, then it could NOT proceed since `emptyA` is already `0`, it need `producerB` to produce a `B` first, but this is impossible because `emptyRepo = 0`, means no producer allowed until repo has empty space.

However this deadlock could be automatically breaked during running as long as consumere keep working, which will increase `emptyRepo` semaphore, so the matter of this order could be consider less essential anyway.