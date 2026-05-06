# Chess Game - User Manual

This guide explains how to interact with the Chess engine.

## Basic Commands

The game operates in a command-line loop. You enter moves or special commands at the prompt.

- **Move a piece**: Enter the starting and ending coordinates without spaces.
  - Example: `e2e4` moves the piece at e2 to e4.
  - Example: `b1c3` moves the knight from b1 to c3.
- **`/quit`**: Exits the game immediately. It will print the final board state in canonical form before closing.
- **`/resign`**: Forfeit the game.
- **`/draw`**: Offer or accept a draw.

## Board Coordinate System

The board uses standard algebraic notation:
- **Columns**: `a` to `h` (from left to right).
- **Rows**: `1` to `8` (from White's side to Black's side).

## Piece Symbols

Due to terminal compatibility issues with UTF-8 symbols on some systems, the board uses the following ASCII representations:

| Symbol | Piece | Color |
| :---: | :--- | :--- |
| `wP` | Pawn | White |
| `wR` | Rook | White |
| `wN` | Knight | White |
| `wB` | Bishop | White |
| `wQ` | Queen | White |
| `wK` | King | White |
| `bP` | Pawn | Black |
| `bR` | Rook | Black |
| `bN` | Knight | Black |
| `bB` | Bishop | Black |
| `bQ` | Queen | Black |
| `bK` | King | Black |

## Gameplay Flow

1. **White moves first**.
2. If a move is illegal (wrong geometry, obstacle in the way, or leaves your King in check), the game will show an error and ask for the move again.
3. If you put the opponent's King in check, a notification will appear.
4. The game ends automatically upon Checkmate or Stalemate.
