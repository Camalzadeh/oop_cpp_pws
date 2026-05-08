# Chessboard Text-mode Game

This directory contains the C++ source code for the chessboard mini-project. The program provides a command-line chess interface, validates moves, handles special chess rules, and prints a canonical final position for automated testing.

## Files

- `main.cpp`: command loop, input parsing, castling notation, promotion notation, and final output.
- `Game.h` / `Game.cpp`: game flow, turns, move validation, special moves, check, checkmate, stalemate, and results.
- `Board.h` / `Board.cpp`: 8x8 board storage, piece placement, canonical output, attack detection, move simulation, promotion, en passant state, captured pieces, and display.
- `Piece.h` / `Piece.cpp`: abstract `Piece` class and concrete `Rook`, `Knight`, `Bishop`, `Queen`, `King`, and `Pawn` movement rules.
- `Square.h`: algebraic coordinate conversion, for example `a1` to row/column indices.
- `Makefile`: separate compilation rules.
- `test/data/`: official level-style test files.
- `tests/run_tests.py`: large archive regression runner.

## Build

With `make`:

```bash
make
```

If `make` is not available, build directly with `g++`:

```powershell
g++ -Wall -std=c++11 -c main.cpp
g++ -Wall -std=c++11 -c Game.cpp
g++ -Wall -std=c++11 -c Board.cpp
g++ -Wall -std=c++11 -c Piece.cpp
g++ -Wall -std=c++11 -o chess main.o Game.o Board.o Piece.o
```

## Run

```powershell
.\chess.exe
```

The program reads from standard input, so it can also be driven by a file:

```powershell
Get-Content .\test\data\1-leg-knight-1.txt | Where-Object { $_ -notmatch '^#' } | .\chess.exe
```

## Input

Supported commands:

- Standard move: `a2a4`, `b1c3`, `e2e4`.
- Kingside castling: `O-O`, `o-o`, or `0-0`.
- Queenside castling: `O-O-O`, `o-o-o`, or `0-0-0`.
- Coordinate castling is also accepted, such as `e1g1`, `e1c1`, `e8g8`, and `e8c8`.
- Promotion prompt: after a pawn reaches the last rank, enter `Q`, `R`, `B`, or `N`.
- UCI promotion input for automated tests: `e7e8q`, `a2a1n`, etc.
- `/quit`: stop the game with result `?-?`.
- `/resign`: current player resigns.
- `/draw`: stop the game with result `1/2-1/2`.

## Display

The board is printed with coordinates `a` through `h` and `1` through `8`. Pieces are displayed with ASCII labels for terminal compatibility:

| Label | Piece |
| --- | --- |
| `wK`, `bK` | White/Black king |
| `wQ`, `bQ` | White/Black queen |
| `wR`, `bR` | White/Black rook |
| `wB`, `bB` | White/Black bishop |
| `wN`, `bN` | White/Black knight |
| `wP`, `bP` | White/Black pawn |

The display also includes a material balance bar and captured pieces. This extra display does not affect automated grading because the final line is still the canonical result line.

## Implemented Requirements

### Level 1: Base

- Displays the chessboard and pieces.
- Accepts ordinary coordinate moves.
- Alternates White and Black turns.
- Handles `/quit`, `/resign`, and `/draw`.
- Prints the final canonical position and game result as the final line.
- Validates board coordinates, origin occupancy, piece movement geometry, captures, pawn moves, and obstacles.
- Rejects illegal moves without changing the board.

### Level 2: Check Detection

- Reports when the opponent's king is in check.
- Rejects moves that leave the current player's king in check.

### Level 3: Special Moves

- En passant capture.
- Castling with `O-O` and `O-O-O`.
- Pawn promotion to queen, rook, bishop, or knight.

### Level 4: Checkmate and Stalemate

- Detects checkmate and sets result to `1-0` or `0-1`.
- Detects stalemate and sets result to `1/2-1/2`.

## Final Output

The last line has exactly:

```text
canonical_position result
```

The canonical position traverses the board in this order:

```text
a1,b1,c1,d1,e1,f1,g1,h1,a2,b2,...,h8
```

Each square is separated by a comma. Empty squares are blank between commas. Pieces use `w` or `b` plus one of `K`, `Q`, `R`, `B`, `N`, or `P`.

Example:

```text
wR,wN,wB,wQ,wK,wB,wN,wR,wP,wP,wP,wP,wP,wP,wP,wP,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,bP,bP,bP,bP,bP,bP,bP,bP,bR,bN,bB,bQ,bK,bB,bN,bR, ?-?
```

## Tests

Run the large regression suite:

```powershell
python .\tests\run_tests.py
```

Results are written to:

- `tests/outputs/test_summary.log`
- `tests/outputs/test_failures.log`

Run the official level-style tests:

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
        }
    }
}
```

Current verification:

- Official level tests: passed.
- Archive runner: `Passed: 20058, Failed: 0`.

