Here we have four traditional storage allocation algorithms.

Traditional:

- FF (First Fit)
- NF (Next Fit)
- BF (Best Fit)
- WF (Worst Fit)

Notice this four algorithms are all **sequential** (顺序分配算法).

> Check Textbook P140 for more info

New:

- Quick Fit
- Buddy System
- Hash

# FF (First Fit)

This means everytime we need to allocate storage (memory), we scan the available block from the start, **use the first one we found that could meet the size requirement**.

# NF (Next Fit)

Improve `FF`, scan not start from beginning, but from the stop position of last time.

# BF

Use the block of the minimum size that could meet requirements. (Reduce waste)

# WF

The opposite of `BF`, choose the biggest one.

# Quick Fit

Create a linklist for the available blocks with same size, for example `2KB`, `4KB`, `8KB` etc.

Set a index table to record these linklist:

- 0 `addr of 2kb linklist`
- 1 `addr of 4kb linklist`
- etc

This method **do NOT divide any block**.

# Buddy System

Check Textbook P142 for more info.