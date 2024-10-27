
# Task: BAZ - Bazaar

## Description

Young Bajtek is spending his vacation with his grandmother Bajtula. Every morning, she goes to the bazaar to buy some products. Bajtek quickly noticed an interesting pattern: every day, his grandmother spends an amount that is an odd integer. He soon realized that this pattern is characteristic of all grandmothers in the Bajtoc region.

Each day, Grandmother Bajtula buys at most one unit of each of the **n** products available at the bazaar. To avoid carrying too much money, she asked Bajtek to help determine the minimum amount she needs if she plans to buy exactly **k** products. Unfortunately, Bajtek does not know which products she intends to buy, so the amount must be enough for any selection of **k** products (ensuring their total cost is odd). This situation has repeated itself multiple times, so Bajtek decided to approach it methodically and write a program to answer his grandmother's queries, given the prices of all products available at the bazaar.

## Input

- The first line contains a single integer **n** (where \(1 \leq n \leq 1,000,000\)), the number of products available at the bazaar.
- The second line contains **n** integers, each in the range \([1, 10^9]\), representing the prices of the products, listed in non-decreasing order.
- The third line contains a single integer **m** (where \(1 \leq m \leq 1,000,000\)), representing the number of days Bajtek will spend with his grandmother.
- Each of the next **m** lines contains a single integer **k_i** (where \(1 \leq k_i \leq n\)), representing the number of products Grandmother intends to buy on day **i**.

## Output

The program should output **m** lines. The **i**-th line (for **i = 1, ..., m**) should contain a single integer representing the maximum odd total cost of **k_i** products. If it is impossible to select **k_i** products with an odd total cost, the **i**-th line should contain **-1**.

## Example

For the following input:
```
4
1 2 3 4
3
2
3
4
```

the correct output is:
```
7
9
-1
```

### Explanation of the Example

In this example:
- For **k = 2**, the maximum odd sum of any two products is **7**.
- For **k = 3**, the maximum odd sum of any three products is **9**.
- For **k = 4**, it is impossible to obtain an odd sum, so the output is **-1**.

