# Mini-project Object Programming: Chessboard

This repository contains a text-mode chess program written in C++ for the Object Programming mini-project. The program reads moves from standard input, updates an internal chessboard model, displays the position, and prints the final canonical position plus the game result on the last output line.

The implementation is in [`project/`](project/).

## Implemented Levels

- **Level 1: Base**
  - Text-mode board display.
  - Algebraic coordinate moves such as `b1c3` and `e2e4`.
  - White/Black turn alternation.
  - `/quit`, `/resign`, and `/draw`.
  - Final canonical position and result output.
  - Coordinate, origin-square, movement-geometry, capture, pawn, and obstacle validation.
- **Level 2: Check Detection**
  - Detects when a king is in check.
  - Rejects moves that leave the moving side's king in check.
- **Level 3: Special Moves**
  - Castling with `O-O` and `O-O-O`, plus coordinate forms such as `e1g1`.
  - En passant.
  - Pawn promotion to `Q`, `R`, `B`, or `N`.
  - UCI-style promotion input such as `e7e8q` is supported for tests.
- **Level 4: Endgame Detection**
  - Checkmate detection and final result.
  - Stalemate detection and final result.

## Build and Run

From PowerShell:

```powershell
cd D:\oop_project\oop_cpp_pws\project
g++ -Wall -std=c++11 -c main.cpp
g++ -Wall -std=c++11 -c Game.cpp
g++ -Wall -std=c++11 -c Board.cpp
g++ -Wall -std=c++11 -c Piece.cpp
g++ -Wall -std=c++11 -o chess main.o Game.o Board.o Piece.o
.\chess.exe
```

On a Unix-like environment with `make`:

```bash
cd project
make
./chess
```

## Test Commands

Run the large archive test runner:

```powershell
cd D:\oop_project\oop_cpp_pws\project
python .\tests\run_tests.py
```

Run the official level-style text tests:

```powershell
cd D:\oop_project\oop_cpp_pws\project

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

