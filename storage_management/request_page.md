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

> Since we should face something like page swap, so the page table should store more auxilary info.

## About Outer Storage

When `P` is `true`, means this page already in memory, we don't need to consider _Outer Storage Addr_.

When `P` is `false`, `M` is `false`. Means this page has not been mutated, this time _Outer Storage Addr_ shall __directly point to storage__. Next time we need, we get it directly from storage.

When `P` is `false`, `M` is `true`. Means this page has been mutated and swapped out. This time _Outer Storage Addr_ __points to swap storage area__ (对换区), where we could find this page next time we need it.

## Minimum Physical Allocated Page

Although we don't need to load all page to memory, there is min alloc page limitation.

In basic simple computer, we need `2` physical block, one for _instruction_, one for _data_.

In computer that support _indirect addressing (间接寻址)_, we need at least `3` blocks. 

For more complicated computer, the instruction is long so it may be stored in two different page, and source data and targeted data may also both stored in two different pages. In conclusion, we need `6` blocks.

> If we don't allocate minimum needed block number, program may malfunction.