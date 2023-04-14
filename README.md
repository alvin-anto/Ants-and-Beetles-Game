# Ants and Beetles Game

This project simulates a game board containing two types of creatures: ants and beetles. Ants and beetles have different behaviors, which are implemented in the derived classes Ant and Beetle inherited from the base class Creature. The simulation runs in a grid environment where ants and beetles move, breed, and interact with each other.

**Features**

- Ants and beetles move in a 2D grid environment.
- Ants move away from the nearest beetles in one of the four cardinal directions (North, East, South, or West).
- Beetles move towards the nearest ants to eat them.
- Both ants and beetles can breed and generate offspring in adjacent grid cells.
- Beetles can starve if they don't eat for a certain number of turns.

**Files**

- Creature.h: The abstract base class for the Ant and Beetle classes.
- Ant.h: The header file for the Ant class, which inherits from the Creature class.
- Ant.cpp: The implementation file for the Ant class, containing the move and breed functions.
- Beetle.h: The header file for the Beetle class, which inherits from the Creature class.
- Beetle.cpp: The implementation file for the Beetle class, containing the move and breed functions.
- main.cpp: The main class that creates the gameboard and plays the game
- world.txt: A sample test file

**Usage**

1) Compile the program using a C++ compiler.
2) Run the compiled executable.
3) Observe the simulation of ants and beetles in the grid environment.

**Requirements**

- A C++ compiler supporting C++11 or later.
