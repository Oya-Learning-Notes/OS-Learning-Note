Banker algorithm is an algorithm to detect possible unsafe states which could cause deadlock before distribute the critical resources to processes.

About _Banker Algorithm_, check out textbook `P123`.

# Exam Answer Format Example

![IMG_2109](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/1ca11504-39f1-4274-948e-0352e547a4f0)

![IMG_2110](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/ac86ce4b-57bb-4011-bd0f-4310618517cf)

# Code Simulation

Check out [Banker's Algorithm C++ Implementation](./banker.cpp)

When we implement this algorithm and start to checking the safety status, we **don't need to copy any of the matrices**, only things we need is:

- temporary available vector (`work` in textbook)
- finished vector (used to mark the finished process)

