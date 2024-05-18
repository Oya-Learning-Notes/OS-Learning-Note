# Request Page Storage Management

This is one kind of virtual storage method.

# Association And Differece with Page Storage

Notice that this concept: _request page storage_ is not same with the one called _page storage_ in chapter 4.

However they could both exist in a same OS and work together (Check out _textbook P170_).

![IMG_3117](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/bca524a3-c2bc-451c-9bf2-c0ec31c9edcd)


The image above explain how _page storage_ and _page request storage_ could work together.

# Schemas of Page Table

- Page Index
- Block Index
- Status Flag `P`
- Access Info `A`
- Mutated Flag `M`
- Outer Storage Address

> Since we should face something like page swap, so the page table should store more auxilary info.\

> Notice that **`P` and `M` usually could be represented by using a single bit**, but **Access Info part could use something like `Interger` to store** (for example store the access time of this page), so **it could use more than one bit**.

## About Outer Storage

| P/M Status        | Outer Sto Meaning                                  |
|-------------------|----------------------------------------------------|
| P is true         | This page is **already in memory**, no need to consider Outer Storage Addr |
| P is false, M is false | Page has not been mutated, Outer Storage Addr **directly points to storage** |
| P is false, M is true  | Page has been mutated and swapped out, Outer Storage Addr **points to swap storage area** |


# Minimum Physical Allocated Page

Although we don't need to load all page to memory, there is min alloc page limitation.

In basic simple computer, we need `2` physical block, one for _instruction_, one for _data_.

In computer that support _indirect addressing (间接寻址)_, we need at least `3` blocks. 

For more complicated computer, the instruction is long so it may be stored in two different page, and source data and targeted data may also both stored in two different pages. In conclusion, we need `6` blocks.

We could **use a table to conclude the information above**:

| Condition                                             | Min Physical Blocks |
|-------------------------------------------------------|---------------------|
| Basic simple computer (1 instruction, 1 data)         | 2                   |
| Computer supporting indirect addressing               | 3                   |
| Complex computer (instruction and data in multiple pages) | 6                   |


> If we don't allocate minimum needed block number, program may malfunction.

# Memory Alloc Strategy

From more conservative to more open:

- _Fixed_ Allocation, _Local_ Replacement
- _Variable_ Allocation, _Local_ Replacement
- _Variable_ Allocation, _Global_ Replacement

When _Allocation_ is _Fixed_, __the block size of the program is fixed__. Else if it's _Variable_, means the __blocks count that allocated to a program could become more or less (that is, dynamic/variable) in runtime__.

When _Replacement_ is _Local_. Means when a program need to swap in a page, __it could only swap out one of it's own page at exchange__. Else if it's _Global_, means __one program could swap out page of other programs__.

| Strategy                              | Allocation Behaviour                                                         | Replacement Behaviour                                       |
|---------------------------------------|-----------------------------------------------------------------------------|------------------------------------------------------------|
| Fixed Allocation, Local Replacement   | The block size of the program is fixed.                                      | It could only swap out one of its own pages at exchange.    |
| Variable Allocation, Local Replacement| The blocks count allocated to a program could become more or less at runtime.| It could only swap out one of its own pages at exchange.    |
| Variable Allocation, Global Replacement| The blocks count allocated to a program could become more or less at runtime.| One program could swap out pages of other programs.         |


> For more info, checkout _Textbook P171_.