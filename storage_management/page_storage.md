# Page Storage

Page storage basically split a program into different __page__, and OS should maintain a page table that __associate program logical page number with the real memory block number__.

## Traditional Access Process

![IMG_2129](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/6e5706bb-03a1-44f1-bc04-7a27f021805d)

In the process above, we first access page table (in memory) to map the logical page number into real memory block number.

Then we combine the _block number_ with the _in-page offset number_, and access memory again to get the data.

In this case, we:

- Access page address register `1` time.
- Access memory for `2` times.
- Legal Check for `1` time.

## Fast Table Boost Access Process

![IMG_2130](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/4069db80-4afb-45bc-8856-05a4d78aa1f9)

In this situation we used a fast table (which can perform parallel mapping) to store some frequently-used page to block map.

In this case:

If hit cache in fast table:

- Access fast table register for `1` time.
- Access memory (to retrive data) for `1` time.
- Legal check for `1` time.

If _NOT_ hit the cache.

- Access fast table register for `3` times.
- Access memory for `2` times.ory (to retrive data) for `1` time.
- 

Here is explanation.

First program check _fast table_, if hit, we got the `block index`, combine it with the `inpgae offset` to access _memory_ to get the data. Process finsihed.

When not hit, First check _fast table_, not hit, so access _page address register_, then access _memory page table_, get the block number, access _memory_ again to get data, access _fast table_ to remember this page id to block id map.