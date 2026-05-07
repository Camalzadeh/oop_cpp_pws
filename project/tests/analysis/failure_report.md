# Chess Engine Failure Analysis Report

This report analyzes the failures encountered during the large-scale testing with 20,000+ Lichess games.

## 📊 Summary of Findings

Based on the logs in `test_summary.log` and `test_failures.log`, the current engine fails in approximately **70-80%** of real-world game scenarios. The failures are almost exclusively due to unimplemented or partially implemented **Level 3** chess rules.

---

## 🛠 Detailed Flaws & Bugs

### 1. Missing Castling Logic (Critical)
- **Symptom**: `FAILED (Illegal move)` or `FAILED (No piece at origin)`.
- **Root Cause**: The `King::is_legal_move` method restricts movement to exactly 1 square. In SAN/UCI, castling is represented as `e1g1` or `e1c1`. Our engine rejects these as illegal.
- **Impact**: Since castling is a standard opening move, once it fails, the engine's internal board state diverges from the real game state. All subsequent moves involving the King or Rooks will fail with "No piece at origin".

### 2. Incomplete Pawn Promotion
- **Symptom**: `FAILED (Illegal move)`.
- **Root Cause**: In `Game.cpp`, when a pawn reaches the 8th rank, it prints "Promotion!", but it **does not replace** the `Pawn` object with a `Queen` (or other piece) in the `Board` array.
- **Impact**: The piece remains a `Pawn`. When the test script sends a "Queen-like" move for that piece later, the engine rejects it because a Pawn cannot move that way.

### 3. Missing En Passant
- **Symptom**: `FAILED (Illegal move)`.
- **Root Cause**: The engine does not track the "double-step" history of pawns. If a pawn tries to capture "into an empty square" via En Passant, the engine rejects it because it only allows diagonal captures if an enemy piece is physically on the target square.

### 4. Turn Desynchronization (Cascading Failure)
- **Symptom**: `FAILED (It's not your turn)`.
- **Root Cause**: When a move is rejected as "Illegal", the `Game::move` function does not switch the turn to the opponent. However, the automated test script continues to send the opponent's next move.
- **Impact**: This creates a permanent desync where the script thinks it's Black's turn, but the engine is still waiting for a legal White move.

### 5. Checkmate/Stalemate Computational Cost
- **Observation**: The `has_legal_moves` function is called after every move. While correct, it simulates every possible move for every piece.
- **Improvement**: In mid-to-end games with many pieces, this causes a slight delay. While not a "bug", it slows down high-speed testing.

---

## 💡 Recommendations for Fixes

1. **Implement Castling**: Update `King::is_legal_move` to allow 2-square horizontal moves if conditions are met, and update `Board::move` to move the Rook simultaneously.
2. **Fix Promotion**: Update `Game::move` to delete the Pawn and instantiate a new `Queen` (default) at the destination square.
3. **Add En Passant State**: Store the last moved pawn's position in the `Board` class to validate En Passant captures.
4. **Move Validation Refactoring**: Ensure that illegal moves are handled gracefully without breaking the game flow for external scripts.

---
*Report generated on: 2026-05-07*
