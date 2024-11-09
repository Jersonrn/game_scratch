# GameFromScratch

A simple game developed using SDL2 as a personal project to learn C++.

## Features

This game includes the following features:

- **Collision Detection**: Basic collision mechanics to interact with game objects.
- **Movement System**: Smooth character movement controls.
- **Animator**: Animation handling for character sprites.
- **Input Handling**: Responsive input system for keyboard controls.
- **Rendering**: Efficient rendering of game graphics.

## Future Enhancements

In future updates, I plan to implement:

- **Collision Triggers**: Advanced collision detection for interactive elements.
- **Sound Effects**: Audio integration for a more immersive experience.
- **Vector Class**: A custom vector class for improved mathematical operations.

## Assets

The art assets used in this game are sourced from the Godot demo platformer. You can find them [here](https://github.com/godotengine/godot-demo-projects/tree/4.2-31d1c0c/2d/platformer).

## Getting Started

To run the game, ensure you have SDL2 installed on your system. Follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Jersonrn/GameFromScratch.git

2. **Navigate to the project directory:**
   ```bash
   cd GameFromScratch

3. **Compile the project**
   ```bash
   mkdir build
   cd build
   cmake ..
   make

4. **Run the game:**
You can run the game with the following command, where the argument `true` enables collision visualization and `false` disables it:
   ```bash
   ./main true

