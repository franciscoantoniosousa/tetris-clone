# Tetris Clone

A simple Tetris clone implemented in C++ using the SFML (Simple and Fast Multimedia Library). This project is a fun way to dive into game development, practicing your C++ skills, and learning how to work with graphics and user input in SFML.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Screenshots](#screenshots)
- [Installation](#installation)
- [How to Play](#how-to-play)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction
This project is a Tetris clone built with **C++** and **SFML**. It includes classic Tetris features such as random tetromino generation, rotation, line clearing, and increasing difficulty as you progress. It is designed to be simple and lightweight, making it a great foundation for further development or as a learning project.

## Features
- Fully playable Tetris game
- Random tetromino generation
- Basic scoring and level progression
- Simple 2D graphics using SFML
- Smooth movement and rotation of tetrominos
- Line clearing with increasing speed as the game progresses
- Game over screen

## Screenshots
![Tetris Clone](path/to/screenshot.png)

> Add a screenshot here to showcase your game.

## Installation

### Prerequisites
Make sure you have the following installed:
- **C++17** or higher
- **SFML 2.5** or higher

### Clone the repository:
\`\`\`bash
git clone https://github.com/your-username/tetris-clone.git
cd tetris-clone
\`\`\`

### Build Instructions (Linux/macOS)
1. Install SFML using your package manager or manually:
   \`\`\`bash
   sudo apt-get install libsfml-dev  # On Ubuntu
   brew install sfml  # On macOS
   \`\`\`
2. Compile the project:
   \`\`\`bash
   mkdir build
   cd build
   cmake ..
   make
   \`\`\`
3. Run the game:
   \`\`\`bash
   ./tetris-clone
   \`\`\`

### Build Instructions (Windows)
1. Download and install SFML from [the official SFML website](https://www.sfml-dev.org/download.php).
2. Use **CMake** or your favorite IDE (like Visual Studio) to configure and build the project.
3. Link the required SFML libraries (`sfml-graphics`, `sfml-window`, `sfml-system`).
4. Build and run the game.

## How to Play
The objective of the game is to move and rotate falling tetromino pieces to create horizontal lines without gaps. When a line is completed, it disappears, and the player earns points. The game ends when the pieces stack to the top of the screen.

## Controls
- **Left Arrow**: Move tetromino left
- **Right Arrow**: Move tetromino right
- **Up Arrow**: Rotate tetromino
- **Down Arrow**: Soft drop tetromino
- **Spacebar**: Hard drop tetromino
- **P**: Pause/Resume the game
- **Escape**: Quit the game

## Project Structure
\`\`\`
tetris-clone/
├── src/                # Source code files
│   ├── Game.cpp        # Main game logic
│   ├── Tetromino.cpp   # Tetromino class implementation
│   └── ...             # Other game components
├── include/            # Header files
│   ├── Game.h
│   ├── Tetromino.h
│   └── ...
├── assets/             # Game assets (fonts, images, etc.)
├── CMakeLists.txt      # Build configuration
└── README.md           # Project documentation
\`\`\`

## Contributing
Contributions are welcome! If you have any ideas for new features, optimizations, or bug fixes, feel free to open an issue or submit a pull request.

To contribute:
1. Fork the repository.
2. Create a new branch for your feature or fix:
   \`\`\`bash
   git checkout -b feature/new-feature
   \`\`\`
3. Commit your changes:
   \`\`\`bash
   git commit -m "Add new feature"
   \`\`\`
4. Push to the branch:
   \`\`\`bash
   git push origin feature/new-feature
   \`\`\`
5. Open a pull request.

## License
### SFML

SFML - Copyright (C) 2007-2023 Laurent Gomila - laurent@sfml-dev.org

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software.  If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

### External libraries used by SFML

  * _OpenAL-Soft_ is under the LGPL license
  * _stb_image_ and _stb_image_write_ are public domain
  * _freetype_ is under the FreeType license or the GPL license
  * _libogg_ is under the BSD license
  * _libvorbis_ is under the BSD license
  * _libflac_ is under the BSD license
  * _minimp3_ is under the CC0 license
