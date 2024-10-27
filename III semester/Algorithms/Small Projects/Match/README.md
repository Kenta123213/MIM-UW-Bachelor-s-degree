
# Task: MEC - Matches

## Description

This task involves a training session with a football team of **n** players (where **n** is an even number). In each match, all players participate, divided into two teams of **n/2** players each. The coach aims to arrange team compositions in such a way that each pair of players has the opportunity to play against each other in at least one match (i.e., play on opposing teams at least once).

However, in practice, some players (despite the coach's efforts) end up playing together on the same team in all matches. The largest subset of players who always play together in the same team across all matches is called a **clique**.

The coach has already proposed the teams for the upcoming **m** matches. Help him determine how close he is to achieving his goal by calculating the size of the largest clique of players.

## Input

The first line of input contains two integers, **n** and **m** (where \(4 \leq n \leq 40,000\) and \(1 \leq m \leq 50\)), representing the number of players and the number of scheduled matches, respectively. Players are numbered from **1** to **n**.

Each of the next **m** lines contains **n** unique integers in the range from **1** to **n**, describing the team compositions for each match. The first **n/2** numbers in each line are the player numbers for the first team, and the second **n/2** numbers are the player numbers for the second team.

## Output

The program should output a single integer representing the size of the largest clique of players.

## Example

For the following input:
```
6 3
4 6 1 3 5 2
1 4 5 2 3 6
1 2 6 4 5 3
```

the correct output is:
```
1
```

For the input:
```
6 3
4 6 1 3 5 2
1 4 5 2 3 6
1 2 3 4 5 6
```

the correct output is:
```
2
```

### Explanation of the Example

In the first example, every pair of players plays on opposing teams in one match (e.g., players numbered 1 and 6), in two matches (e.g., players 1 and 2), or even in all three matches (e.g., players 1 and 3). The division of players into cliques is therefore: {1}, {2}, {3}, {4}, {5}, {6}.

In the second example, players numbered 2 and 3 always play on the same team. The division of players into cliques is therefore: {1}, {2, 3}, {4}, {5}, {6}.
