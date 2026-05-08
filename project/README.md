# Chess Project - C++ OOP Implementation

Terminal chess game for an Object-Oriented Programming course project. The program provides a command-line chess interface, validates ordinary and special chess moves, and prints a canonical final position for automated grading.

## Files

- `main.cpp`: command loop, input parsing, castling notation, promotion notation, and final output.
- `Game.h` / `Game.cpp`: game flow, turns, results, promotion prompts, checkmate, and stalemate.
- `Board.h` / `Board.cpp`: board storage, piece ownership, move execution, castling, en passant, promotion, attack detection, and canonical output.
- `Piece.h` / `Piece.cpp`: abstract `Piece` class and concrete `Rook`, `Knight`, `Bishop`, `Queen`, `King`, and `Pawn` movement rules.
- `Square.h`: algebraic coordinate conversion, for example `a1` to row/column indices.
- `Makefile`: build rules.
- `test/data/`: level-style test files.
- `tests/run_tests.py`: automated regression test runner.

## Build

In the `project` directory:

```bash
make
```

Or compile directly:

```powershell
g++ -std=c++17 -O2 main.cpp Board.cpp Game.cpp Piece.cpp -o chess.exe
```

## Run

On Windows PowerShell:

```powershell
.\chess.exe
```

The program reads from standard input, so it can also be driven by a file:

```powershell
Get-Content .\test\data\1-leg-knight-1.txt | Where-Object { $_ -notmatch '^#' } | .\chess.exe
```

## Commands

- Ordinary move: `e2e4`
- Promotion with prompt: move the pawn to the last rank, then enter `Q`, `R`, `B`, or `N`
- UCI-style promotion: `e7e8q`, `a2a1n`, etc.
- Kingside castling: `O-O`, `o-o`, or `0-0`
- Queenside castling: `O-O-O`, `o-o-o`, or `0-0-0`
- Coordinate castling: `e1g1`, `e1c1`, `e8g8`, or `e8c8`
- Quit: `/quit`
- Exit alias: `/exit`
- Resign: `/resign`
- Draw: `/draw`

## Features Implemented

- Standard piece movement, captures, and alternating turns.
- Obstacle blocking for rook, bishop, and queen.
- Check detection with illegal self-check rejection.
- Checkmate and stalemate detection.
- Kingside and queenside castling, including occupied-square and attacked-square checks.
- En passant.
- Pawn promotion to queen, rook, bishop, or knight.
- English class and method names: `Game`, `Board`, `Piece`, `King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`.
- Canonical grading output with stable piece codes: `wK`, `wQ`, `wR`, `wB`, `wN`, `wP`, `bK`, `bQ`, `bR`, `bB`, `bN`, `bP`.

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
wR,wN,wB,wQ,wK,wB,wN,wR,wP,wP,wP,wP,wP,wP,wP,wP,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,bP,bP,bP,bP,bP,bP,bP,bP,bR,bN,bB,bQ,bK,bB,bN,bR ?-?
```

## Manual Test Sequences

Normal moves:

```text
e2e4
e7e5
g1f3
b8c6
/quit
```

En passant:

```text
e2e4
a7a6
e4e5
d7d5
e5d6
/quit
```

Checkmate:

```text
f2f3
e7e5
g2g4
d8h4
```

## Tests

Run the archive regression suite:

```powershell
python .\tests\run_tests.py
```

Run the level-style tests after building `chess.exe`:

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

## Documentation

- [User Manual](docs/MANUAL.md)
- [Architecture & Logic](docs/ARCHITECTURE.md)
