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

## Calculate Maximum Program Size

When only use one physical memory block to store the page table, what's the maximum size of a program?

Consider we could use `4B` to represents a physical block number. And We have `2^10 x 1B` memory block unit. Then result will be like the img below:

![IMG_2133](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/75524ac1-5be9-4e85-9041-7581910c9b2c)

When using a single block, the maximum page count will be:

```
2^12 (B) / 4 (B)
= 2^10 (Pages)
= 1K (Pages)
```

For one single page, the size would be `2^12` Byte. So the answer is:

```
Max Size = 1K * 2^12 K
         = 2^10 * 2^12 (B)
         = 2^22 B
         = 4 MB
```

# Inverted Page Table (反置页表)

This could so the large size problem of the multi-level page table solution.

The page table above, we __store physical block index__ in the page table.

## Is it save size?

Let's consider a `64 MB`(`2^26 B`) memory. And each pages has `4 KB` (`2^12 B`) size.

There is `2^26 / 2^12` = `2^14` max possible pages.

If we use __inverted page table__, means we need to __store logical page number in page table__. We know the range is `[0, 2^14)`, this could be represents using two bytes. (2 bytes could represents `[0, 2^16)`).

64KB = 2^16 B