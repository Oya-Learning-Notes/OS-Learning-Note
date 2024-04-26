# Prerequesities Of Deadlock

- Resource is mutual exclusion.
- Hold and wait.
- No preemption.
- Circular set.

# Deal With Deadlock

- (预防) Prevention (Just try prevent, still have chance to form a deadlock)
- (避免) Avoidance (Use algorithm and rules to make it impossible)
- Unlock (Solve a deadlock)

# Avoidance

How to avoid a deadlock? There are several methods.

## Request All At The Same Time

Program must request all resources at the same time. 

This break condition `Keep and hold`.

## Failed Then Release

If you can't not obtain the new resources, release all others you already kept.

This break condition `No preemption`.

## Circular Set Detection & Avoidance

Use resources algorithm to check before distribute resources to avoid circular set.

That's what banker algorithm does.

Check out [Banker Algorithm Notes](./banker_algo.md) for more info.