*This project has been created as part of the 42 curriculum by eldiaz-c, ptrapero.*

#  cub3D

## Description

cub3D is a graphical project inspired by the classic game Wolfenstein 3D. The objective is to create a simple first-person 3D renderer using raycasting techniques and the MiniLibX graphical library.

The program reads a `.cub` configuration file containing the map layout, wall textures, floor and ceiling colors, and player starting position. Using raycasting, it renders a pseudo-3D environment where the player can move around the map while colliding with walls and viewing textured surfaces.

This project introduces concepts such as:

* Raycasting
* Texture mapping
* Event handling
* Collision detection
* Basic game loop architecture
* Mathematical transformations using vectors and trigonometry

---

## Features

* First-person 3D rendering using raycasting
* Textured walls
* Floor and ceiling colors
* Collision detection
* Player movement and rotation
* Minimap
* Map validation and parsing
* Frame rate limiting

---

## Instructions

### Compilation

Clone the repository and run:

```bash
make
```

This will generate the executable:

```bash
./cub3D
```

### Execution

Run the program with a valid `.cub` map:

```bash
./cub3D maps/map.cub
```

### Controls

| Key | Action        |
| --- | ------------- |
| W   | Move forward  |
| S   | Move backward |
| A   | Move left     |
| D   | Move right    |
| ←   | Rotate left   |
| →   | Rotate right  |
| ESC | Exit          |

---

## Project Structure

* `init/` → variables initialization
* `hooks/` → keyboard and window events
* `parse/` → map and configuration parsing
* `render/` → raycasting and drawing functions
* `utils/` → helper functions

---

## Technical Notes

The 3D scene is generated using the Digital Differential Analyzer (DDA) algorithm. A ray is cast for every vertical screen column to determine wall intersections and calculate the correct wall height on screen.

Texture mapping is applied by determining the exact hit position on the wall and selecting the corresponding column from the texture image.

To avoid the fish-eye effect, perpendicular wall distances are used instead of direct Euclidean distances.

---

## What We Learned

During the development of this project, we gained practical experience with several fundamental concepts in graphics programming and software development.

### Computer Graphics

* Understanding how raycasting works to create a pseudo-3D environment from a 2D map.
* Using the DDA (Digital Differential Analyzer) algorithm to efficiently detect wall intersections.
* Calculating perpendicular distances to avoid the fish-eye effect.
* Applying texture mapping to walls using hit coordinates.
* Managing frame rendering and screen drawing with MiniLibX.

### Mathematics

* Working with trigonometric functions (`sin`, `cos`, `atan2`) to calculate movement and ray directions.
* Understanding vectors and direction planes.
* Using coordinate transformations between world space and screen space.
* Applying geometric reasoning to collision detection and rendering calculations.

### Programming

* Organizing a medium-sized C project.
* Managing memory and resources correctly.
* Parsing and validating complex configuration files.
* Handling keyboard events and user interaction.
* Debugging graphical and mathematical issues.

### Teamwork

* Designing and maintaining a shared project architecture.
* Dividing tasks and integrating independent components.
* Reviewing and refactoring code collaboratively.
* Solving rendering and gameplay problems through discussion and experimentation.

This project provided a practical introduction to the techniques behind early first-person games and strengthened our understanding of graphics programming, mathematics, and software architecture in C.

---

## Resources

### References

* Raycasting Tutorial: https://www.youtube.com/watch?v=G9i78WoBBIU
* Lode's Computer Graphics Tutorial https://lodev.org/cgtutor/raycasting.html
* Trigonometry and vector references
* MiniLibX documentation

### Use of AI

AI tools were used as a learning aid during the development of the project.

The assistance mainly focused on:

* Understanding raycasting mathematics
* Explaining trigonometric calculations
* Debugging rendering issues
* Discussing texture mapping concepts
* Reviewing code organization and architecture ideas

All generated explanations and suggestions were reviewed, adapted and implemented manually by the authors.

---

## Authors

* eldiaz-c
* ptrapero
