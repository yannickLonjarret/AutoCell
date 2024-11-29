# Conway's Game of Life

This project is a C++ implementation of **Conway's Game of Life**, developed as part of a programming assignment for M3301 during the 2021-2022 academic year. The project was created by Claire Cardona, Théo Fée, and Yannick Lonjarret.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Rules of the Game](#rules-of-the-game)
5. [Code Structure](#code-structure)
6. [Acknowledgments](#acknowledgments)

---

## Introduction

The **Game of Life** is a cellular automaton devised by John Conway. It simulates the evolution of a grid of cells based on simple rules of birth, survival, and death. Each cell interacts with its eight neighbors, and its state changes over successive steps, forming fascinating patterns.

This implementation allows users to:
- Define the size of the grid.
- Initialize live cells at specific coordinates.
- Simulate the game for a specified number of steps.

---

## Features

- **Interactive User Input**: Define the initial configuration of live cells and number of simulation steps.
- **Dynamic Grid Updates**: Automatically updates and displays the grid at each step.
- **Rule Implementation**: Implements all standard rules of Conway's Game of Life.
- **Visualization**: Clearly displays live cells (`O`) and dead cells (`x`).

---

## Rules of the Game

1. **Underpopulation**: A live cell with fewer than two live neighbors dies.
2. **Overpopulation**: A live cell with more than three live neighbors dies.
3. **Survival**: A live cell with two or three live neighbors survives.
4. **Reproduction**: A dead cell with exactly three live neighbors becomes a live cell.
---

## Code Structure

### Main Functions

1. **AfficherRegles**:
   - Displays the rules of Conway's Game of Life.

2. **InitialisationGrille**:
   - Initializes the grid based on user input.

3. **Simulation**:
   - Runs the simulation for a specified number of steps.

4. **AfficherGrille**:
   - Displays the current state of the grid.

### Supporting Functions

- **NombreEtapes**: Prompts the user to input the number of steps.
- **RemplirGrille**: Sets up the initial live cells.
- **MajGrille**: Updates the grid by applying the game rules.
- **NombreVoisinVivant**: Counts the live neighbors for a given cell.
- **ChangementEtat**: Determines the next state of a cell based on its neighbors.

---

## Acknowledgments

This project was developed as part of the academic curriculum for M3301. Special thanks to our instructor, Mr. Marhic, for guidance and support throughout the project.

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---

Enjoy exploring the fascinating world of Conway's Game of Life!

