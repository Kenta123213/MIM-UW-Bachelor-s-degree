
# Task: SOR - Bucket Sort

## Description

**Bucket Sort** is an interesting algorithm with high time complexity for sorting. The algorithm operates in steps, meaning it performs a sequence of operations on a given sequence until the sequence becomes sorted in non-decreasing order.

The sorting step involves analyzing the sequence from left to right and building an auxiliary sequence as the result of that step. At the beginning of the step, the first element of the current sequence is added to the auxiliary sequence. Each subsequent element is then placed either at the beginning of the auxiliary sequence if the previous element of the original sequence was greater than it or at the end if the previous element was smaller.

For example, in one step of the algorithm, the sequence `5, 6, 2, 1, 4, 3` transforms through the following auxiliary sequences:
- `5`
- `5, 6`
- `2, 5, 6`
- `1, 2, 5, 6`
- `1, 2, 5, 6, 4`
- `3, 1, 2, 5, 6, 4`

The last sequence in this list is the result of that sorting step.

Your task is to "unsort" the given sequence, i.e., determine how many different sequences transform into the given sequence in one step of the bucket sort algorithm.

## Input

The input consists of:
- The first line containing a single integer **n** (where \(1 \leq n \leq 1000\)).
- The second line containing **n** unique integers from the set \(\{1, \dots, n\}\), representing the sequence to be "unsorted."

## Output

The output should be the remainder when dividing by \(10^9\) the number of different sequences that, in one step of bucket sort, transform into the given sequence.

## Example

For the following input:
```
4
1 2 3 4
```

the correct output is:
```
8
```

For the input:
```
4
4 3 2 1
```

the correct output is:
```
0
```

### Explanation of the Example

In one step of the bucket sort algorithm, the following sequences transform into `1, 2, 3, 4`:
- `1, 2, 3, 4`
- `4, 3, 2, 1`
- `2, 1, 3, 4`
- `3, 2, 1, 4`
- `2, 3, 1, 4`
- `2, 3, 4, 1`
- `3, 4, 2, 1`
- `3, 2, 4, 1`

In contrast, no other sequence transforms into `4, 3, 2, 1` in a single step.
