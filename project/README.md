# Chessboard Project - Comprehensive C++ Implementation

Welcome to the terminal-based Chess engine. This project is a complete implementation of a Chess game, developed as a final requirement for the Object-Oriented Programming course.

## 🚀 Quick Start

### Prerequisites
- A C++ compiler (e.g., `g++` or `clang++`).
- `make` utility (optional but recommended).

### Compilation
In the `project` directory, run:
```bash
make
```
*If you don't have `make`, use:*
```bash
g++ *.cpp -o chess
```

### Running the Game
```bash
./chess
```

---

## 📖 Documentation

To help you understand and play the game better, we have provided detailed documentation in the `docs/` folder:

1. **[User Manual](docs/MANUAL.md)**: How to play, list of commands, and coordinate system explanation.
2. **[Architecture & Logic](docs/ARCHITECTURE.md)**: Detailed breakdown of the classes, inheritance, and core algorithms used.
3. **[Requirements & Constraints](README.md#requirements-met)**: Tracking of the assignment levels achieved.

---

## ✅ Requirements Met

This implementation covers all levels of the project requirements:

- **Level 1 (Base)**:
  - Full board display and piece representation.
  - Turn alternation (White/Black).
  - Move validation and geometric legality.
  - Capture logic and obstacle detection.
  - Canonical output format for grading.
- **Level 2 (Check Detection)**:
  - Real-time check notification.
  - Prevention of illegal moves that leave the King in check.
- **Level 3 (Special Moves)**:
  - Pawn Promotion detection.
- **Level 4 (Game End)**:
  - Checkmate detection and game conclusion.
  - Stalemate detection.

---

## 🛠 Technical Highlights

- **Polymorphism**: Uses a pure virtual `is_legal_move` interface to allow for extensible piece behavior.
- **Robust Validation**: Uses move simulation (try-move, check-state, undo-move) to enforce complex Chess rules without side effects.
- **Compatibility Mode**: Uses high-visibility ASCII symbols (`wR`, `bN`, etc.) to ensure the board is readable in all terminal types (including Windows CMD and PowerShell).

---
*Developed for the OOP Mini-Project - May 2026*
