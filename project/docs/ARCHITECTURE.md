# Software Architecture

This document describes how the project maps to the required object-oriented chessboard model.

## Class Overview

### `Square`

`Square` represents one coordinate on the 8x8 board.

Responsibilities:

- store row and column indices,
- convert algebraic input such as `a1` into internal indices,
- validate whether coordinates are inside the board,
- convert a square back to text form.

### `Piece`

`Piece` is an abstract base class. It stores data shared by every chess piece:

- color,
- current position,
- whether the piece has moved.

It declares the polymorphic methods:

```cpp
virtual char pieceCode() const = 0;
virtual bool isLegalMove(Square destination, const Board& board) const = 0;
```

The concrete subclasses are:

- `Rook`
- `Knight`
- `Bishop`
- `Queen`
- `King`
- `Pawn`

Each subclass implements its own movement geometry. Sliding pieces use `Board::isPathClear()` to check obstacles.

### `Board`

`Board` owns and manages the chessboard state.

Main data:

- `Piece* board[8][8]`: the actual board cells,
- `std::vector<Piece*> pieces[2]`: active pieces for each color,
- `hasEnPassant`, `enPassantTarget`, and `enPassantPawn`: en passant state,
- `lastForceMoveHadMoved`: state saved for reversible simulations.

Main responsibilities:

- initialize the starting position,
- place and retrieve pieces,
- execute ordinary moves and captures,
- validate and execute castling,
- track and execute en passant,
- promote pawns,
- detect attacks and checks,
- generate the canonical final position,
- simulate and undo moves for legality checking,
- search legal moves for checkmate and stalemate detection.

### `Game`

`Game` coordinates the rules and user-level game flow.

Responsibilities:

- track the current turn and move number,
- execute requested moves through `Board`,
- reject illegal moves without changing the turn,
- prompt for promotion when needed,
- detect check, checkmate, and stalemate after legal moves,
- maintain the game result.

### `main.cpp`

`main.cpp` handles the command-line loop:

- reads standard input,
- parses commands such as `/quit`, `/exit`, `/resign`, and `/draw`,
- parses ordinary moves like `e2e4`,
- parses castling notation `O-O` and `O-O-O`,
- parses UCI-style promotion notation such as `e7e8q`,
- prints the final canonical line.

## Move Validation Flow

1. Convert origin and destination strings to `Square` objects.
2. Verify both coordinates are valid.
3. Verify the origin contains a piece.
4. Verify the piece belongs to the current player.
5. Call the piece's polymorphic `isLegalMove()` method, or detect an en passant exception.
6. Reject captures of friendly pieces.
7. Simulate the move and reject it if it leaves the moving side's king in check.
8. Execute captures, en passant removal, or the ordinary move.
9. Promote a pawn if it reaches the final rank.
10. Check whether the opponent is in check.
11. Check whether the opponent has legal moves.
12. Set checkmate or stalemate result if needed.
13. Switch turns.

## Special Move Handling

### Castling

`Board::canCastle()` verifies that the king and rook are on their starting squares, neither piece has moved, the king is not currently in check, the path is empty, and the king does not cross or land on an attacked square. `Board::castle()` then moves both pieces.

The input parser accepts `O-O`, `o-o`, `0-0`, `O-O-O`, `o-o-o`, and `0-0-0`. Coordinate forms such as `e1g1` and `e8c8` are also handled because a two-column king move is routed to castling.

### En Passant

When a pawn moves two squares, the square it crossed is stored as `enPassantTarget` and the pawn itself is stored as `enPassantPawn`. On the next move only, an opposing pawn may capture diagonally into the target square, and the passed pawn is removed.

### Promotion

When a pawn reaches row 8 for White or row 1 for Black, it is replaced by a new `Queen`, `Rook`, `Bishop`, or `Knight` object. The choice is provided either by an interactive prompt or by UCI-style input like `a7a8q`.

## Checkmate and Stalemate

After every legal move, the game checks whether the opponent is in check and whether the opponent has at least one legal move.

- No legal move and in check: checkmate.
- No legal move and not in check: stalemate.

The search is implemented by trying possible destination squares for each active piece and simulating moves with `wouldLeaveKingInCheck()`.

## Canonical Position

`Board::canonicalPosition()` traverses:

```text
a1,b1,c1,d1,e1,f1,g1,h1,a2,b2,...,h8
```

Each square is encoded as:

- `w` or `b` for color,
- `K`, `Q`, `R`, `B`, `N`, or `P` for piece type,
- empty text for an empty square,
- comma separators between squares.
