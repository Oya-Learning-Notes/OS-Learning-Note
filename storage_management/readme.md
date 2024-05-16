This directory is used to store notes about the Chapter 4 -- Storage management. And Chapter 5 Virtual Storage.

> Textbook P129

# Chapter 4

In this chapter, we have:

- 分区分配
    - 固定分区
    - 动态分区
        - 动态分区算法* ([Link](./alloc_algo.md))
        - 紧凑
- 对换
    - 换出之后可能的空闲块合并* (P139)

- 分页储存* ([Link](./page_storage.md))
    - 多级页表
    - 反置页表
- 分段储存
- 段页储存

# Chapter 5

- 请求分页储存管理([Link](./request_page.md))
    - 页面对换算法
- 请求分段储存管理

## Why we call it virtal storage

Here we explain why this chapter called __virtal storage__.

Virtual is a conception to _memory_. In one word, we __pretend that we have a much more memory that we actually not__. How we achieve this? We lie to program, tell them all they need is ready, but actually we just take it when they want to use it.

And that's what Page Request Storage and Segment Request Storage has done.