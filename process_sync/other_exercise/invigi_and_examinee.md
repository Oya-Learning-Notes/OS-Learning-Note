# Problem Description

There is a classroom used for an exam which could contain up to `N` students. The door only allow one student go in and out at a time. Invigilator should distribute the paper after all student arrived the classroom, and only leave after all student handed in their paper.

# Binary Semaphore Solution

Below is a solution that only using binary semaphore value (that means the value of semaphore could be either `0` or `1`)

```cpp
const int N;        // max capacity of the classroom
int stuInClass = 0; // record current count of the students in the class
// semaphore inClassMutex = 1; feature of this semaphore could be combined into `doorMutex`

semaphore allInClass = 0;  // signal for all student already in class
semaphore allHandedIn = 0; // signal for all student already handed in their answer

// record if exam already start or end
semaphore examStart = 0;
semaphore examEnd = 0;

semaphore doorMutex = 1; // protect only one student cross the door

void student()
{
    // go into classroom
    wait(doorMutex);
    ++stuInClass;
    enterClassroom();
    if (stuInClass == N)
    {
        signal(allInClass);
    }
    signal(doorMutex);

    // wait for start then do paper and hand in
    wait(examStart);
    doPaper();
    handIn();

    // leave
    wait(doorMutex);
    --stuInClass;
    leaveClassroom();
    if (stuInClass == 0)
    {
        signal(examEnd);
    }
    signal(doorMutex);
}

void invigilator()
{
    // go into classroom (but no need to mutate stuInClass)
    wait(doorMutex);
    intoClass();
    signal(doorMutex);

    // wait all arrive
    wait(allInClass);
    distributePaper();
    // signal examStart multiple times, otherwise there would only one student be able to start doing his paper
    for (int i = 0; i < N; ++i)
    {
        signal(examStart);
    }

    // wait exam end
    wait(examEnd);
    dealWithHandedInPaper();
    leaveClassroom(); // at this time we could prove already no students in the classroom
}
```

## Implementation Details

Notice that we directly call `leaveClassroom()` without acquiring `doorMutex`, this is because in this code we could promise when `examEnd = 1` that must mean all student already left the classroom.

# Refs

[CSDN - Invigilator And Examinee Model](https://blog.csdn.net/bai38572/article/details/101090102)