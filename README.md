# Angry Birds Clone

This is a learning clone of the Angry Birds game, written in C++ using the SFML and Box2D libraries.

## Screenshot
![MainMenuScreen](https://github.com/user-attachments/assets/c7d918e6-09bb-46c5-beba-1f4b4d3f94b8)

## Features

- Box2D physics for object movement simulation
- Graphics and sound via SFML
- Multiple levels, menu, score counting
- Different types of birds and enemies

## Requirements

- Visual Studio 2015 or newer (x64 recommended)
- C++ compiler with C++11/14 support
- [SFML](https://www.sfml-dev.org/) (included in `Dependencies/SFML`)
- [Box2D](https://box2d.org/) (included in `Dependencies/Box2D`)

## How to Run

1. Open the solution [`AngryBirds.sln`](angry-birds-clone/AngryBirds.sln) in Visual Studio.
2. Select configuration (Debug/Release, x64).
3. Build the project (`Build Solution`).
4. Run the project (`Start`).

## Structure

- `AngryBirds/` — main game code (`.cpp` and `.h` files)
- `Dependencies/` — external libraries (SFML, Box2D)
- `Assets/` — resources (textures, sounds, fonts) **(create this folder if it doesn't exist and add the required files)**

## Main Files

- [`main.cpp`](angry-birds-clone/AngryBirds/main.cpp) — entry point
- [`Game.h`](angry-birds-clone/AngryBirds/Game.h), [`Game.cpp`](angry-birds-clone/AngryBirds/Game.cpp) — main game logic

## Notes

- For correct operation, make sure all SFML DLLs are located next to the executable file.
- If you encounter issues running the game, check resource paths in the code.
