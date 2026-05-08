# Chess Project - C++ OOP Implementation

Terminal chess game for an Object-Oriented Programming course project.

## Quick Start

In the `project` directory:

```bash
make
```

Or compile directly:

```bash
g++ -std=c++17 -O2 *.cpp -o chess.exe
```

Run the game:

```bash
./chess
```

On Windows PowerShell:

```powershell
.\chess.exe
```

## Documentation

Detailed documentation is available in the `docs/` folder:

1. [User Manual](docs/MANUAL.md): How to play, commands, and coordinate system.
2. [Architecture & Logic](docs/ARCHITECTURE.md): Breakdown of classes and core algorithms.

## Commands

- Ordinary move: `e2e4`
- Kingside castling: `O-O`, `o-o`, or `0-0`
- Queenside castling: `O-O-O`, `o-o-o`, or `0-0-0`
- Quit: `/quit`
- Resign: `/resign`
- Draw: `/draw`

## Manual Test Sequences

Enter each move on its own line after starting the program with `./chess` or `.\chess.exe`.

Normal moves:

```text
e2e4
e7e5
g1f3
b8c6
/quit
```

Invalid empty-square move:

```text
e3e4
/quit
```

Invalid own-piece capture:

```text
e1e2
/quit
```

Capture:

```text
e2e4
d7d5
e4d5
/quit
```

Check and self-check rejection:

```text
f2f3
e7e5
e2e4
d8h4
a2a3
/quit
```

Kingside castling:

```text
e2e4
e7e5
g1f3
b8c6
f1e2
g8f6
O-O
/quit
```

Queenside castling:

```text
d2d4
d7d5
b1c3
g8f6
c1e3
b8c6
d1d2
e7e6
O-O-O
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

Promotion:

```text
a2a4
h7h5
a4a5
h5h4
a5a6
h4h3
a6b7
h3g2
b7a8
Q
/quit
```

Checkmate:

```text
f2f3
e7e5
g2g4
d8h4
```

Stalemate:

```text
e2e3
a7a5
d1h5
a8a6
h5a5
h7h5
h2h4
a6h6
a5c7
f7f6
c7d7
e8f7
d7b7
d8d3
b7b8
d3h7
b8c8
f7g6
c8e6
```

The final line printed by the program is the grading line:

```text
canonical_position result
```

## Features Implemented

- Standard piece movement, captures, and turn validation.
- Check detection with illegal self-check rejection.
- Checkmate and stalemate detection.
- Kingside and queenside castling, including attacked-square checks.
- En passant.
- Real pawn promotion to Queen, Rook, Bishop, or Knight.
- English class and method names: `Game`, `Board`, `King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`.
- Canonical grading output with stable piece codes: `wK`, `wQ`, `wR`, `wB`, `wN`, `wP`, `bK`, `bQ`, `bR`, `bB`, `bN`, `bP`.
