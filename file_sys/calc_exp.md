An example of the Calculation Question in _File System_.

- Indexing
- FCB _(File Control Block)_
- Multi-Layer Indexing. _(增量索引)_

# Question

![IMG_3269](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/ed4036a5-4c11-479c-b8e7-55482164ddc8)

# Q1: Calculate Total Indexable Size

![IMG_2188](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/706be976-7138-4299-8d54-caaeb04592bd)

# Q2: Calculate Average Access Time

![IMG_2189](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/5d320435-97b2-4d48-ab57-f6dc29f8d4ec)

## Notice

- Add `1` To Avg Access Time When Using Optimized Block

Description: When using this **Optimized Node** method _(which means use the more lightweight block for search)_, we need to **add `1` to Avg Storage Access Time**.

Reason: Because when we find the lightweight block, we need to access storage one extra time to find out and read the full FCB.

# Calculate FAT Size

![IMG_2190](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/8f528cd4-18c0-44ad-9eb9-8b5b16d2d45e)

# Refs

Original PPT Image:

<details>
<summary>Original PPT Images</summary>
    
![IMG_3269](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/feeb6be5-7f4b-4ad2-9632-61c6c2c75d09)

![IMG_3270](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/da46af51-d004-4be9-87b9-085c1ec57825)

![IMG_3273](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/14485355-fc95-4938-8e8c-6c07a8d0254d)

![IMG_3274](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/da164028-2739-4154-92a6-babd122eb4ad)

</details>