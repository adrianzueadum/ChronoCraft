# ChronoCraft: A 2D Time-Manipulation Puzzle Game

## Overview
ChronoCraft is an innovative 2D puzzle game built in C++ using the SFML library. Players control a character who can rewind and fast-forward time to manipulate environmental objects (e.g., moving platforms, destructible barriers) and solve intricate puzzles. The game combines time-based mechanics with strategic planning, offering a unique experience distinct from traditional platformers or puzzle games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, physics-based puzzles, and creative mechanics. By sponsoring ChronoCraft via GitHub Sponsors, you support ongoing development, new puzzle designs, and community-driven tutorials.

## Features
- **Time Manipulation**: Rewind or fast-forward time to alter object states and solve puzzles.
- **Dynamic Environments**: Interact with moving platforms, switches, and destructible objects.
- **Clean Art Style**: Minimalist 2D graphics with a focus on clear, responsive gameplay.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code, ideal for learning and extending.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/chronocraft.git
   cd chronocraft
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./ChronoCraft
   ```

## Gameplay
- **Objective**: Navigate to the level exit by manipulating time to solve puzzles.
- **Controls**:
  - **A/D**: Move left/right.
  - **Space**: Jump.
  - **Q/E**: Rewind/fast-forward time.
  - **R**: Reset level.
  - **Esc**: Pause or exit.
- **Mechanics**: Rewind time to restore broken platforms or undo mistakes. Fast-forward to skip hazardous cycles (e.g., moving lasers). Plan your moves to align environmental objects correctly.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (player, platforms, switches).
- `src/Game.hpp`: Core game logic, time manipulation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
We welcome contributions! Fork the repo, create a feature branch, and submit a pull request. For major changes, please open an issue to discuss your ideas.

## Sponsorship
Support ChronoCraft’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions enable:
- New puzzle levels and mechanics.
- Enhanced time-manipulation features.
- Tutorials for C++ and game development.
- Performance optimizations and broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by time-based puzzle games and creative problem-solving.
- Gratitude to the open-source community for feedback and inspiration.

---

**Sponsor ChronoCraft to help craft the future of puzzle gaming!**