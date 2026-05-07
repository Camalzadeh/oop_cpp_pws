# Chess Project - C++ OOP Implementation

Terminal chess game for an Object-Oriented Programming course project.

## Quick Start

In the `project` directory:

```bash
g++ -std=c++17 -O2 *.cpp -o chess.exe
```

On Linux or macOS with `make` installed:

```bash
make
```

## Commands

- Ordinary move: `e2e4`
- Kingside castling: `O-O`, `o-o`, or `0-0`
- Queenside castling: `O-O-O`, `o-o-o`, or `0-0-0`
- Quit: `/quit`
- Resign: `/resign`
- Draw: `/draw`

## Technical Highlights

- English class and method names: `Game`, `Board`, `King`, `Queen`, `Rook`, `Bishop`, `Knight`, `Pawn`.
- Polymorphic piece movement through `isLegalMove`.
- Reversible move simulation for check, checkmate, stalemate, castling safety, and en passant safety.
- Real pawn promotion to Queen, Rook, Bishop, or Knight.
- Canonical grading output uses stable piece codes: `wK`, `wQ`, `wR`, `wB`, `wN`, `wP`, `bK`, `bQ`, `bR`, `bB`, `bN`, `bP`.
