# Software Architecture

This document describes the internal structure and logic of the Chess engine.

## Class Hierarchy

### 1. `Square`
- **Responsibility**: Represents a single cell on the 8x8 grid.
- **Key Logic**: Converts algebraic notation (e.g., "a1") into internal row/column indices (0-7) and vice versa.

### 2. `Piece` (Abstract Base Class)
- **Responsibility**: Defines the interface for all chess pieces.
- **Inheritance**: Subclasses (`Rook`, `Knight`, `Bishop`, `Queen`, `King`, `Pawn`) implement the `is_legal_move` method.
- **Polymorphism**: The board interacts with pieces through `Piece*` pointers, allowing dynamic resolution of movement rules.

### 3. `Board`
- **Responsibility**: Manages the 8x8 array of piece pointers.
- **Key Methods**:
  - `move()`: Executes a validated move.
  - `is_check()`: Determines if a King is under attack.
  - `has_legal_moves()`: Scans all possible moves for a side to detect Checkmate/Stalemate.
  - `force_move()` / `undo_force_move()`: Used for "look-ahead" simulations to verify if a move leaves the King in check.

### 4. `Game`
- **Responsibility**: Orchestrates the game flow.
- **Logic**: 
  - Validates user input.
  - Alternates turns between White and Black.
  - Tracks turn count for the prompt display.
  - Checks for end-game conditions (Mate/Stale).

## Core Logic Flows

### Move Validation Process
1. Parse input string into two `Square` objects.
2. Verify coordinates are within bounds.
3. Verify the origin square contains a piece of the current player's color.
4. Call `Piece::is_legal_move()` (Geometric check + obstacle check).
5. Simulate the move using `force_move()`.
6. Check `Board::is_check()` for the current player.
7. If check exists, undo move and report error.
8. If no check, finalize the move.

### Checkmate Detection
After every successful move, the engine calls `Board::has_legal_moves()` for the opponent. If the opponent has no legal moves AND is in check, it's Checkmate. If they have no legal moves but are NOT in check, it's Stalemate.
