# Chess Game User Manual

This guide explains how to build, run, and use the text-mode chess program.

## Starting the Program

From the project directory:

```powershell
.\chess.exe
```

The program can also read from standard input:

```powershell
Get-Content .\test\data\1-leg-knight-1.txt | Where-Object { $_ -notmatch '^#' } | .\chess.exe
```

## Interface

The game displays an 8x8 board with columns `a` through `h` and rows `1` through `8`. White starts at row `1`, Black starts at row `8`.

The prompt shows the move number and active side:

```text
1. White -> (eg. e2e4) ?
```

## Move Input

Enter moves using origin and destination coordinates:

```text
e2e4
b1c3
a7a5
```

The program checks:

- coordinates are inside the board,
- the origin contains a piece,
- the piece belongs to the current player,
- the movement geometry is legal,
- sliding pieces do not jump over pieces,
- pawns move and capture correctly,
- a move does not capture a friendly piece,
- a move does not leave the moving side's king in check.

If a move is illegal, the board is left unchanged and the same player moves again.

## Special Commands

- `/quit`: ends the game as interrupted, result `?-?`.
- `/exit`: alias for `/quit`.
- `/resign`: current player resigns.
- `/draw`: ends the game as a draw, result `1/2-1/2`.

## Special Moves

### Castling

Kingside castling:

```text
O-O
```

Queenside castling:

```text
O-O-O
```

The parser also accepts lowercase `o` and zero `0`, for example `0-0`. Coordinate forms such as `e1g1`, `e1c1`, `e8g8`, and `e8c8` are also supported.

### En Passant

En passant is supported when a pawn has just advanced two squares and an opposing pawn can capture it as if it had advanced one square.

### Promotion

When a pawn reaches the final rank, the program asks:

```text
Promotion! Choose piece (Q, R, B, N):
```

Enter one of:

- `Q`: queen
- `R`: rook
- `B`: bishop
- `N`: knight

For automated UCI-style input, the program also accepts moves such as `e7e8q`.

## Piece Labels

The board display and canonical output use machine-readable labels:

| Label | Piece |
| --- | --- |
| `wK`, `bK` | White/Black king |
| `wQ`, `bQ` | White/Black queen |
| `wR`, `bR` | White/Black rook |
| `wB`, `bB` | White/Black bishop |
| `wN`, `bN` | White/Black knight |
| `wP`, `bP` | White/Black pawn |

## Check, Checkmate, and Stalemate

After a legal move:

- the program reports if the opponent is in check,
- checkmate ends the game with `1-0` or `0-1`,
- stalemate ends the game with `1/2-1/2`.

## Final Line for Testing

When the program exits, the last line is:

```text
canonical_position result
```

Result is exactly one of:

- `1-0`
- `0-1`
- `1/2-1/2`
- `?-?`

This final line is the line used by automated test scripts.
