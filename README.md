# Raycasting and Gravity Simulation using SDL 🎮

## Overview 📌
This project demonstrates a **raycasting simulation with gravity effects**, implemented using **SDL (Simple DirectMedia Layer)** in C. The simulation features a primary circle casting rays, interacting dynamically with another moving circle under gravity, creating an engaging visual effect.

## Features ✨
- **Raycasting System**: A central circle emits `400` rays that dynamically interact with objects.
- **Gravity Physics**: Circles experience acceleration due to gravity and bounce upon collision.
- **Mouse Interaction**: Move circles by dragging the mouse.
- **Dynamic Color Transition**: Smooth color transitions for a visually appealing effect.

## Simulation Preview 🖼️
![![Simulation Screenshot](https://github.com/raunaksingh9800/SDL/blob/main/PREVIEW.png)] 

---

## Code Breakdown 📖
### 1️⃣ Struct Definitions
#### **Circle Structure**
```c
struct Circle {
    double x, y, r, vy, BOUNCE_DAMPING;
};
```
- `x, y`: Position of the circle.
- `r`: Radius of the circle.
- `vy`: Velocity along the Y-axis (gravity effect).
- `BOUNCE_DAMPING`: Controls bounce energy loss.

#### **Line Structure**
```c
struct Line {
    double x1, y1, x2, y2;
};
```
- Represents a line segment using two points.

#### **RGB Color Structure**
```c
struct RGB {
    uint8_t r, g, b;
};
```
- Defines colors for rendering elements.

### 2️⃣ Circle Drawing Algorithm
```c
void DrawCircle(SDL_Surface* surface, struct Circle* c, struct RGB* rgb)
```
- Renders a filled circle using **pixel-by-pixel** rendering.

### 3️⃣ Line Drawing Algorithm (Bresenham's Line Algorithm)
```c
void DrawLine(SDL_Surface* surface, struct Line* line, struct RGB* rgb, struct Circle* col_c, int count)
```
- Implements **Bresenham’s Line Algorithm** for efficient line rendering.
- Checks for intersections with the moving circle.

### 4️⃣ Raycasting Mechanism
```c
void CastRay(SDL_Surface* surface, struct Circle* c, struct Line* l, struct RGB* color, struct Circle* col_c, int count)
```
- Casts rays in **all directions** from the central circle.
- Each ray extends up to `WIDTH + BLEED` pixels.

### 5️⃣ Gravity and Physics Simulation
```c
if (circle.y + circle.r < HEIGHT) {
    circle.vy += GRAVITY * TIME_STEP;
    circle.y += circle.vy;
} else {
    circle.y = HEIGHT - circle.r;
    circle.vy = -circle.vy * circle.BOUNCE_DAMPING;
}
```
- Simulates gravity on both circles.
- Implements **bounce damping** to reduce energy loss upon hitting the ground.

### 6️⃣ Event Handling (Mouse Interaction)
```c
if (e.type == SDL_MOUSEMOTION && e.motion.state != 0) { }
```
- Allows the user to drag circles using the mouse.

---

## Installation & Execution 🚀
### Prerequisites 🛠️
Ensure you have **SDL2** installed:
```bash
sudo apt install libsdl2-dev # Linux
brew install sdl2           # macOS
```

### Compilation ⚙️
```bash
gcc -o simulation simulation.c -lSDL2 -lm
```

### Run the Simulation 🎮
```bash
./simulation
```

---

## Future Enhancements 🚀
- ✅ Implement collision detection between rays and objects.
- ✅ Improve rendering performance with optimized algorithms.
- ✅ Add real-time UI controls for user interaction.

## Author 🎨
- **Raunak Singh**

## License 📜
This project is **open-source** and available for modification under the **MIT License**.

---
Happy Coding! 🎉

