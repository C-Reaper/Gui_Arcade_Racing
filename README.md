# Project README

## Overview
This project is a simple implementation of the classic arcade game "Astroids" using C and a custom GUI library. The game features a spaceship that can move and shoot asteroids, which the player must destroy to advance.

## Features
- Player-controlled spaceship with movement and shooting mechanics.
- Asteroids that randomly generate and move across the screen.
- Collision detection between the spaceship and asteroids.
- Basic game loop for updating game state and rendering graphics.
- Sound effects (not fully implemented in the provided code).

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- X11 library for GUI functionality on Linux
- Windows API for GUI functionality on Windows
- ALSA library for audio output on Linux

## Build & Run

### Linux Build process:
```bash
cd <Project>
make -f Makefile.linux all
```

To execute the built application:
```bash
./build/Main
```

### Windows Build process:
```bash
cd <Project>
make -f Makefile.windows all
```

To execute the built application:
```bash
.\build\Main.exe
```

### Wine Build process (for Linux cross-compiling for Windows):
```bash
cd <Project>
make -f Makefile.wine all
```

To run the Windows executable on Linux using Wine:
```bash
wine build/Main.exe
```

### Webassembly Build process:
First, ensure you have Emscripten installed. Then:

```bash
cd <Project>
make -f Makefile.web all
```

To execute the built application in a web browser:
```bash
emrun --no_browser --port 8080 build/index.html
```

### Build Options
- `make -f Makefile.linux all`: Build the output for Linux.
- `make -f Makefile.windows all`: Build the output for Windows.
- `make -f Makefile.wine all`: Build the output for Linux cross-compiling for Windows.
- `make -f Makefile.web all`: Build the output for Webassembly.
- `make -f Makefile.linux do`: Build + execute the output for Linux.
- `make -f Makefile.windows do`: Build + execute the output for Windows.
- `make -f Makefile.wine do`: Build + execute the output for Linux (cross-compiling for Windows).
- `make -f Makefile.web do`: Build + execute the output for Webassembly.
- `make -f Makefile.linux clean`: Remove build artifacts for Linux.
- `make -f Makefile.windows clean`: Remove build artifacts for Windows.
- `make -f Makefile.wine clean`: Remove build artifacts for Wine (Linux cross-compiling).
- `make -f Makefile.web clean`: Remove build artifacts for Webassembly.