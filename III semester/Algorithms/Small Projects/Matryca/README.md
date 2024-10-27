
# Task: MAT - Matrix

## Description

The **Bajtoc Printing House** (BZP) received a large order to produce striped wallpapers, a seasonal hit in interior design. Each wallpaper consists of **n** vertical stripes of equal width and different colors. BZP is responsible for designing and printing these wallpapers. The client has predefined the colors of certain stripes on the wallpaper, while leaving the remaining stripes up to BZP's discretion.

To print the wallpapers, BZP uses printing matrices that cover a specific number of consecutive stripes on the wallpaper. The matrix has predetermined colors for each of its stripes and may be shorter than the entire wallpaper. If a matrix has **k** stripes, it can be applied in all **n−k+1** possible positions where its stripes align with the wallpaper stripes, printing all the matrix stripes at each position. As a result, a single stripe on the wallpaper may be printed over multiple times. If a stripe is printed in different colors, the final color will be a blend of those colors.

The BZP staff, regardless of their aesthetic preferences, aim to design the **shortest possible matrix** that can produce the entire wallpaper. They must ensure that for stripes specified by the client, they use the exact color without any mixing. In other words, whenever the matrix is applied over such a stripe, the stripe's color in the matrix must match the client's specification.

## Input

The input consists of a single line containing a string of uppercase Latin letters and asterisks (`*`), representing the desired appearance of the wallpaper. Individual letters denote specific stripe colors, while asterisks represent stripes with unspecified colors. The length of the string **n** satisfies \(1 \leq n \leq 1,000,000\).

## Output

The program should output a single integer, **k**, representing the minimum length of the matrix that allows printing the required wallpaper.

## Example

For the following input:
```
A*B*B*A
```

the correct output is:
```
6
```

### Explanation of the Example

A matrix of length 6 that would produce the wallpaper specified in the input (consisting of seven stripes) could be `ABBBBA`.

