Reversi Game Implementation
Introduction
The game of Reversi, also known as Othello, is played on a 64-square board, divided into rows numbered from 1 to 8 and columns labeled from a to h. Board positions are named by indicating the column first, followed by the row.

Reversi is played with black-and-white two-sided pieces. Each square on the board can hold at most one piece. If the piece is black-side up, it is called a black piece; if it’s white-side up, it’s called a white piece.

A game of Reversi begins with white pieces on squares d4 and e5 and black pieces on squares d5 and e4. All other squares are empty.

The game involves two players, Black and White, named after the color of the pieces they control. The Black player always starts the game.

Players take turns, placing a piece of their color on the board. If all pieces in a line (row, column, or diagonal) between the placed piece and another piece of the same color are of the opposite color, those pieces are flipped to the current player’s color. Placing one piece may flip multiple lines of pieces at once.

A move is legal only if it flips at least one piece on the board. If a player cannot make a legal move, they must pass their turn without placing a piece.

For the purposes of this task, we allow players to skip their turn even if a legal move is available, which is not permitted under standard Reversi rules.

Another rule we will not enforce is the automatic end of the game when neither player can make a legal move. In standard rules, the player with more pieces on the board at this point is declared the winner.

Task
Write a program that enables two players to play Reversi.

The program, in a loop:

Displays a prompt indicating which player’s turn it is and what legal moves are available.
Reads the current player’s command.
If the command is to end the game, the program stops.
If the command is to skip the turn, the program returns to the beginning of the loop.
If the command is to make a move, it performs the move and then returns to the beginning of the loop.
The program does not terminate until the end-game command is issued, even if neither player has a legal move available. It does not treat skipping a turn or ending the game as an error, even if a legal move is possible.

Data Format
The input consists of commands from players. Each command occupies one line, and all commands are in the correct format.

End game command: A line containing =.
Skip turn command: A line containing -.
Move command: A line with the name of a board position.
Commands to make a move indicate a legal move. Any text after the end-game command is ignored by the program.

Output Format
The program’s output consists of a series of prompt texts. Each prompt occupies one line.

The prompt starts with an indication of the current player:

C indicates the Black player.
B indicates the White player.
The rest of the prompt text is a list of board positions where the player can legally place their piece. The positions are listed in lexicographic order, each preceded by a space.
