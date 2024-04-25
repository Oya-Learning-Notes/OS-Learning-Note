Here is a list of **Realtime Task Schedule Algorithm**.

- EDF (Earliest Deadline First)
- LLF (Least Laxity First)

# EDF

This is too simple so we don't discuss here lol. Only remember to check if the task is ready when you select it.

- Did it in arrive?
- Did it loaded into memory?

# LLF

> Check out textbook P109

First we need to know how to calculate _laxity_ .

```
Laxity = Deadline - CurrentTime - RunningTime
```

For example, a task has deadline `20`, it costs `10` to finish, current time is `5`, then it's laxity is:

```
Laxity = 20 - 5 - 10
       = 15 - 10
       = 5
```

You could consider laxity **how many time you have to rest before you must have to start working** lol.

## Rules in LLF

- Only select ready task.
- Do not switch if possible.
  - Once selected a task, if don't hit condition below, then do not switch.
  - Force swith when there is another task that current laxity is zero.

## Exam Quesion Example

Check out the image below:

![FullSizeRender](https://github.com/Oya-Learning-Notes/OS-Learning-Note/assets/61616918/7abaa177-3882-49df-9a21-b76b1b0dc311)

- Yellow: Selected.
- Red: Next rount not ready.
