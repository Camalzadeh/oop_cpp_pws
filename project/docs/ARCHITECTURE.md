# Software Architecture

This document describes how the project maps to the required object-oriented chessboard model.

## Class Overview

### `Square`

`Square` represents one coordinate on the 8x8 board.

Responsibilities:

- stores row and column indices,
- converts algebraic input such as `a1` into internal indices,
- validates whether coordinates are inside the board,
- converts a square back to text form.

### `Piece`

`Piece` is an abstract base class. It stores data shared by every chess piece:

- color,
- display name,
- current position,
- whether the piece has moved.

It declares the polymorphic method:

```cpp
virtual bool is_legal_move(Square dest, const Board& board) const = 0;
```

The concrete subclasses are:

- `Rook`
- `Knight`
- `Bishop`
- `Queen`
- `King`
- `Pawn`

Each subclass implements its own movement geometry. Sliding pieces use the board to check obstacles.

### `Board`

`Board` owns and manages the chessboard state.

Main data:

- `Piece* board[8][8]`: the actual board cells,
- `std::vector<Piece*> pieces[2]`: active pieces for each color,
- `Square en_passant_square`: en passant target square,
- captured-piece lists for display.

Main responsibilities:

- initialize the starting position,
- place and retrieve pieces,
- move pieces on the board,
- remove and restore pieces,
- promote pawns,
- track en passant state,
- detect attacks and checks,
- generate the canonical final position,
- simulate and undo moves for legality checking,
- search legal moves for checkmate/stalemate detection.

### `Game`

`Game` coordinates the rules and user-level game flow.

Responsibilities:

- track the current turn and move number,
- validate a requested move,
- reject illegal moves without changing the turn,
- execute castling, en passant, promotion, and ordinary moves,
- reject moves that leave the player's own king in check,
- detect check, checkmate, and stalemate,
- maintain the game result.

### `main.cpp`

`main.cpp` handles the command-line loop:

- reads standard input,
- parses commands such as `/quit`, `/resign`, and `/draw`,
- parses ordinary moves like `e2e4`,
- parses castling notation `O-O` and `O-O-O`,
- parses UCI promotion notation such as `e7e8q`,
- prints the final canonical line.

## Move Validation Flow

1. Convert origin and destination strings to `Square` objects.
2. Verify both coordinates are valid.
3. Verify the origin contains a piece.
4. Verify the piece belongs to the current player.
5. Reject same-square moves.
6. Call the piece's polymorphic `is_legal_move()` method.
7. Reject captures of friendly pieces.
8. Detect whether the move is castling or en passant.
9. Simulate the move using `Board::force_move()`.
10. For castling, move the rook as part of the same operation.
11. For en passant, remove the captured pawn.
12. Reject and undo the move if the current player's king is left in check.
13. Promote a pawn if it reaches the final rank.
14. Check whether the opponent is in check.
15. Check whether the opponent has legal moves.
16. Set checkmate or stalemate result if needed.
17. Update en passant state.
18. Switch turns.

## Special Move Handling

### Castling

The king accepts a two-column horizontal move if the king and rook have not moved and the path is clear. `Game` then moves the rook to the correct square.

The input parser maps:

- White `O-O` to `e1g1`
- White `O-O-O` to `e1c1`
- Black `O-O` to `e8g8`
- Black `O-O-O` to `e8c8`

### En Passant

When a pawn moves two squares, the square it crossed is stored as `en_passant_square`. On the next move only, an opposing pawn may capture diagonally into that square, and the passed pawn is removed.

### Promotion

When a pawn reaches row 8 for White or row 1 for Black, it is replaced by a new `Queen`, `Rook`, `Bishop`, or `Knight` object. The choice is provided either by an interactive prompt or by UCI-style input like `a7a8q`.

## Checkmate and Stalemate

After every legal move, the game checks whether the opponent is in check and whether the opponent has at least one legal move.

- No legal move and in check: checkmate.
- No legal move and not in check: stalemate.

The search is implemented by trying possible destination squares for each active piece and simulating moves.

## Canonical Position

`Board::canonical_position()` traverses:

```text
a1,b1,c1,d1,e1,f1,g1,h1,a2,b2,...,h8
```

Each square is encoded as:

- `w` or `b` for color,
- `K`, `Q`, `R`, `B`, `N`, or `P` for piece type,
- empty text for an empty square,
- comma separator after every square.
