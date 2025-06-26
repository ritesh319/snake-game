# 🐍 Snake Game in C++ (Console Version)

This is a classic **Snake Game** implemented in **C++**, playable in the console. It features:
- Dynamic gameplay using keyboard controls (`W`, `A`, `S`, `D`)
- Wall collisions
- Food spawning logic
- Growing snake body
- Score tracking and saving to a file
- Data structures like **deque**, **stack**, and **linked list**

---

## 🎮 Features

- 🚀 Smooth terminal rendering with real-time controls
- 🍎 Food spawns at random positions, avoiding snake body and walls
- 🧱 Static wall borders (edges of the grid)
- 📈 Score system: +10 points per food
- 💾 Score history is saved in a file: `score_history.txt`

---

## 🛠️ Technologies Used

- **Language:** C++
- **Libraries:**  
  - `<iostream>` for input/output  
  - `<conio.h>` and `<windows.h>` for real-time keyboard input and delays (Windows-only)  
  - `<stack>`, `<deque>`, `<vector>` for data structure management  
  - `<ctime>`, `<fstream>` for timestamp and file handling

---

## 🧑‍💻 How to Run

1. **Open in Visual Studio Code or any C++ IDE**
2. Make sure you're on **Windows OS** (due to `conio.h` and `windows.h`)
3. Compile the code:
   ```bash
   g++ snake_game.cpp -o snake_game
4. Run the game:
   ```bash
   ./snake_game
