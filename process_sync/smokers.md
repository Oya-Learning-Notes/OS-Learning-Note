# Problem Description

Consider there is three smokers. Every smoker need three things to make a cigarette and start smoking:

- Tobacco
- Paper
- Match

Three smokers each have infinite one different type of resources, for example first smokers may have infinite tobacco, second one has infinite paper, and third one has infinite match.

There is an agent which will randomly put two different resources onto the desk. The smoker who has the rest one type of resources should get this resources, make a cigarette and somking. When he finished, the agent will again put two different type of resources on the dask, etc.

## Limitations

In the original proposal of this question, there are two limitations to the code implementation:

- Agent code could not be changed once written.
- No conditional jump allowed in smoker processes.
- Only semaphore wait/signal operation allowed.

It's already been proved that **in such condition it would be impossible to solve this problem by using semaphore**, because there will always be a possible deadlock scenario.

Let's try it ourself.

## Only Wait/Signal

Consider we have semaphores listed below:

```
semaphore tobaccoOnDesk = 0;
semaphore paperOnDesk = 0;
semaphore matchOnDesk = 0;
semaphore smokingStopped = 1;
```

First consider the agent code is like below:

```cpp
void agent(){
    wait(smokingStopped); // only when no one is smoking then agent should put something on desk

    int rnd = rand(1, 3); // make a random number in range [1, 3]

    if(rnd != 1) signal(tobaccoOnDesk);
    if(rnd != 2) signal(paperOnDesk);
    if(rnd != 3) signal(matchOnDesk);
}
```

Consider the smokers processes is like:

```cpp
void smokersWithTobacco(int holdingResType){
    wait(paperOnDesk);
    wait(matchOnDesk);
    smoking();
    signal(smokingStopped);
}
```

The other smoker process is similar.

Now you will notice that there has a chance of deadlock. When agent put tobacco and match, then if there is anyone who is not the smoker with paper took away the things from desk, the deadlock will occured.

You may think we could solve this problem by carefully arrange the order of `wait` in smoker process just like what we have done in _dinning philosopher model_ , but you could try yourself and you will finally found that **no matter how you arrange the order of wait, you could not prevent a possible deadlock**.

## Use AND

One solution to this problem may be using the `AND` semaphore wait opeartion.

We need to slightly change our smoker processes into below:

```cpp
void smokerWithTobacco(){
    wait(paperOnDesk, matchOnDesk);
    smoking();
    signal(smokingStopped);
}
```

Other smokers are similar.

In this code, `wait(paperOnDesk, matchOnDesk);` will promise the two lock will either both acquired or all will be released.

# Ref

[Open CSF - Cigarette Smokers Problems](https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/CigSmokers.html)