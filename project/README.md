# Chess Project - C++ OOP Implementation

Terminal chess game developed for an Object-Oriented Programming course project.

The program provides a command-line chess interface, validates ordinary and special chess moves, displays the board with Unicode chess pieces, and prints a canonical final position for automated grading.

## Team Members

- Elshan Shukurov
- Ismayil Yusifli
- Huseyin Pashayev
- Humbat Camalov
- Yunis Kangarli

## Project Overview

This project implements a playable chess game in C++ using Object-Oriented Programming principles.

The implementation covers the required project levels:

1. **Base Game**
   - Board display
   - Move input
   - White/Black turn alternation
   - Basic move validation
   - Captures
   - Pawn movement
   - `/quit`, `/resign`, `/draw` commands

2. **Check Detection**
   - Detects when a king is in check
   - Prevents moves that leave the current player's own king in check

3. **Special Moves**
   - Kingside castling
   - Queenside castling
   - En passant
   - Pawn promotion

4. **End Game**
   - Checkmate detection
   - Stalemate detection
   - Correct game result output

## Files

- `main.cpp`: program entry point, command loop, input parsing, castling notation, promotion notation, and final output.
- `Game.h` / `Game.cpp`: game flow, turns, results, promotion handling, checkmate, and stalemate.
- `Board.h` / `Board.cpp`: board storage, piece ownership, move execution, castling, en passant, promotion, attack detection, and canonical output.
- `Piece.h` / `Piece.cpp`: abstract `Piece` class and concrete `Rook`, `Knight`, `Bishop`, `Queen`, `King`, and `Pawn` movement rules.
- `Square.h`: algebraic coordinate conversion, for example `a1` to row/column indices.
- `Makefile`: build rules.
- `test/data/`: level-style test files.
- `tests/run_tests.py`: automated regression test runner.
- `docs/MANUAL.md`: user manual.
- `docs/ARCHITECTURE.md`: architecture and logic explanation.

## Build Instructions

Open a terminal in the `project` directory.

### Using Makefile

```bash
make
```

### Direct Compilation

If `make` is not available, compile directly with `g++`:

```powershell
g++ -std=c++17 -O2 main.cpp Board.cpp Game.cpp Piece.cpp -o chess.exe
```

## How to Run

On Windows PowerShell:

```powershell
.\chess.exe
```

On Linux/macOS:

```bash
./chess
```

The program displays the chessboard and waits for a move:

```text
1. White -> (eg. e2e4) ?
```

Example game:

```text
e2e4
e7e5
g1f3
b8c6
/quit
```

The program can also read moves from a file through standard input.

Example on Windows PowerShell:

```powershell
Get-Content .\test\data\1-leg-knight-1.txt | Where-Object { $_ -notmatch '^#' } | .\chess.exe
```

## Commands

### Normal Moves

Use coordinate notation:

```text
e2e4
g1f3
b1c3
```

### Castling

Kingside castling:

```text
O-O
o-o
0-0
```

Queenside castling:

```text
O-O-O
o-o-o
0-0-0
```

Coordinate castling is also supported:

```text
e1g1
e1c1
e8g8
e8c8
```

### Promotion

When a pawn reaches the final rank, the player can promote it to:

```text
Q
R
B
N
```

UCI-style promotion is also supported:

```text
e7e8q
a2a1n
```

### Game Commands

```text
/quit
/resign
/draw
/exit
```

Result behavior:

- `/quit` ends the game with `?-?`
- `/draw` ends the game with `1/2-1/2`
- `/resign` gives the win to the opponent
- Checkmate ends the game with `1-0` or `0-1`
- Stalemate ends the game with `1/2-1/2`

## Features Implemented

- Standard legal movement for all pieces.
- Captures.
- White/Black turn alternation.
- Input validation.
- Obstacle blocking for rook, bishop, and queen.
- Knight jumping behavior.
- Pawn one-square movement.
- Pawn two-square first move.
- Pawn diagonal capture.
- Check detection.
- Illegal self-check prevention.
- Checkmate detection.
- Stalemate detection.
- Kingside and queenside castling.
- En passant.
- Pawn promotion.
- Unicode chess-piece board display.
- Canonical grading output with stable piece codes.

## Board Display

The terminal board uses Unicode chess symbols for readability.

White pieces:

```text
♔ ♕ ♖ ♗ ♘ ♙
```

Black pieces:

```text
♚ ♛ ♜ ♝ ♞ ♟
```

This is only for the human-readable board display.

The final canonical output still uses machine-readable codes such as:

```text
wK, wQ, wR, wB, wN, wP
bK, bQ, bR, bB, bN, bP
```

## Final Output Format

The last line printed by the program has exactly:

```text
canonical_position result
```

The canonical position traverses the board in this order:

```text
a1,b1,c1,d1,e1,f1,g1,h1,a2,b2,...,h8
```

Each square is separated by a comma. Empty squares are represented by empty content between commas.

Piece codes:

```text
wK = white king
wQ = white queen
wR = white rook
wB = white bishop
wN = white knight
wP = white pawn

bK = black king
bQ = black queen
bR = black rook
bB = black bishop
bN = black knight
bP = black pawn
```

Possible result strings:

```text
1-0
0-1
1/2-1/2
?-?
```

Example:

```text
wR,wN,wB,wQ,wK,wB,wN,wR,wP,wP,wP,wP,wP,wP,wP,wP,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,bP,bP,bP,bP,bP,bP,bP,bP,bR,bN,bB,bQ,bK,bB,bN,bR, ?-?
```

## Manual Test Sequences

### Normal Moves

```text
e2e4
e7e5
g1f3
b8c6
/quit
```

### En Passant

```text
e2e4
a7a6
e4e5
d7d5
e5d6
/quit
```

### Scholar's Mate

```text
e2e4
e7e5
f1c4
b8c6
d1h5
g8f6
h5f7
```

Expected result:

```text
Checkmate! White wins.
1-0
```

### Fool's Mate

```text
f2f3
e7e5
g2g4
d8h4
```

Expected result:

```text
Checkmate! Black wins.
0-1
```

## Running Tests

First build the program:

```powershell
g++ -std=c++17 -O2 main.cpp Board.cpp Game.cpp Piece.cpp -o chess.exe
```

Run the automated regression suite:

```powershell
python .\tests\run_tests.py
```

or:

```powershell
py .\tests\run_tests.py
```

The expected result is:

```text
Failed: 0
```

Run level-style tests manually:

```powershell
foreach ($level in 1..4) {
    foreach ($file in Get-ChildItem ".\test\data\$level-*.txt" | Where-Object { $_.Name -notlike '._*' }) {
        $output = Get-Content $file.FullName | Where-Object { $_ -notmatch '^#' } | .\chess.exe
        $actual = $output | Select-Object -Last 1
        $expected = Get-Content $file.FullName | Select-Object -Last 1

        if ($actual -eq $expected) {
            "OK   $($file.Name)"
        } else {
            "FAIL $($file.Name)"
            "Expected: $expected"
            "Actual:   $actual"
        }
    }
}
```

## Technical Choices

### Object-Oriented Structure

The project is divided into separate classes to keep responsibilities clear:

- `Square` handles coordinate conversion.
- `Piece` defines the common interface for all chess pieces.
- `Rook`, `Knight`, `Bishop`, `Queen`, `King`, and `Pawn` implement piece-specific movement rules.
- `Board` manages piece storage, movement execution, special moves, attack detection, and canonical output.
- `Game` manages turns, commands, game results, checkmate, and stalemate.

This structure improves readability, modularity, and maintainability.

### Separate Display and Canonical Output

The board display uses Unicode chess pieces to make the terminal game easier to read.

The canonical output remains text-based because automated tests require stable machine-readable codes such as `wK`, `bQ`, and `wP`.

### Move Validation Pipeline

Each move is validated step by step:

1. Parse input.
2. Check coordinates.
3. Check origin square.
4. Check piece color.
5. Check movement rule.
6. Check path blocking.
7. Check special move conditions.
8. Reject moves that leave the player's own king in check.
9. Apply the move.
10. Check for checkmate or stalemate.

## Challenges Faced

- Correctly separating visual board display from canonical grading output.
- Handling special chess rules such as castling, en passant, and promotion.
- Preventing moves that leave the player's own king in check.
- Detecting checkmate and stalemate reliably.
- Keeping the project compatible with automated stdin-based testing.
- Resolving merge conflicts while preserving the final English-named architecture.
- Ensuring Windows terminal output supports Unicode chess symbols.

## Documentation

Additional documentation is available in:

- [User Manual](docs/MANUAL.md)
- [Architecture & Logic](docs/ARCHITECTURE.md)

