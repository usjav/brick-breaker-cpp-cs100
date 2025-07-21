# 🧱 My Brick Breaker – C++ Game

## 🎮 Overview
A classic Brick Breaker replica developed in **C++** as part of my CS 100 coursework. This desktop game features intuitive controls, profile management, multiple difficulty levels, and physics-based gameplay mechanics—all built from scratch without game engines.

Players can create/load profiles, select gameplay difficulty (Easy / Medium / Hard), and enjoy randomized tile layouts with escalating challenge across levels. Game saves persist between sessions, and collision logic is custom-designed for realistic behavior.

## 🧠 Features
- 🎯 **Difficulty Modes**:  
  - Easy: Slow ball / Long bar  
  - Medium: Faster ball / Shorter bar  
  - Hard: Fastest ball / Shortest bar

- 🧪 **Physics Engine**:  
  - Ball rebounds off tiles, borders, and bar  
  - Adaptive speed increases on successful hits  
  - Custom side collision logic on bar edges  

- 🧑‍💻 **User Interface**:  
  - Mouse-controlled bar movement  
  - Menu navigation with arrow keys  
  - Real-time lives and score display  
  - Pause/Resume functionality  
  - Instruction panel accessible via menu

- 💾 **Game State Management**:  
  - Create/load player profiles  
  - Save game progress after level completion or pause  
  - File handling for game saves, user data, and config files

## 🖼️ Instructions
- Use mouse to move paddle along the X-axis  
- Navigate menus using arrow keys  
- Game ends when all lives are lost  
- Score and speed increase as bricks break  
- Difficulty resets after each session

## 🛠️ Setup & Compilation
> Tested on Windows with MinGW and BGI graphics library

### 🔧 Prerequisites
- Install **MSYS2**
- Install **MinGW32**
- Add MinGW to system PATH

### 🧱 Compilation
1. Open `mingw32.exe`
2. Navigate to your working directory
3. Run the following command:
```bash
g++ main.cpp -o game -Igraphics -Lgraphics -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
```
4. Run ```game.exe``` and enjoy!

⚠️ Do not remove the graphics/ folder — it contains essential header and DLL files.

👤 Profile Instructions
- Create a new profile from the main menu
- Load a profile by typing its name
- Game starts with default "Easy" mode and saved data if available

Everything—from tile rendering and collision to game progression and interface—was built from scratch in C++.

📣 Created by usjav for CS 100 project with ❤️
