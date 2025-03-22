# 🎮 SDL Bouncing Circles Simulation

## 📝 Overview
This project is a **simple physics simulation** built using **SDL2 (Simple DirectMedia Layer)**. It features two bouncing circles that simulate gravity, collision with the ground, and user interaction via mouse dragging.

## 🖥️ Features
- 🎨 **Realistic Gravity Effect**: The circles fall under gravity and bounce upon hitting the ground.
- 🖱️ **Mouse Dragging**: Click and drag the circles to move them.
- 🌈 **Dynamic Color Transition**: The larger circle changes color dynamically.
- 🎮 **Smooth Animation**: Runs at approximately **60 FPS** for a fluid visual experience.

---

## 🏗️ How It Works
### Physics Simulation
- The circles fall freely under the influence of **gravity**.
- When they hit the ground, they bounce with a damping factor.
- If their bounce velocity becomes too small, they eventually stop.

### User Interaction
- Moving the mouse while holding the button allows users to **drag the circles**.
- Collision detection ensures accurate movement.

### Color Animation
- The larger circle gradually transitions between **yellow and white**, creating a smooth glowing effect.

---

## 📜 Code Breakdown
### 1️⃣ **Struct Definitions**
```c
struct Circle {
    double x, y, r;   // Position & radius
    double vy;        // Vertical velocity
    double BOUNCE_DAMPING; // Bounce energy loss
};

struct RGB {
    uint8_t r, g, b;
};
```
- `Circle` stores properties of each bouncing ball.
- `RGB` is used for dynamic color changes.

### 2️⃣ **Rendering & Physics**
```c
void DrawCircle(SDL_Surface* surface, struct Circle* c, struct RGB* rgb)
```
- Renders a filled circle by checking if each pixel lies within the radius.

```c
if (circle.y + circle.r < HEIGHT) {
    circle.vy += GRAVITY * TIME_STEP;
    circle.y += circle.vy;
} else {
    circle.y = HEIGHT - circle.r;
    circle.vy = -circle.vy * circle.BOUNCE_DAMPING;
}
```
- Implements basic gravity and bounce physics.

### 3️⃣ **User Interaction**
```c
if (e.type == SDL_MOUSEMOTION && e.motion.state != 0) {
    if (circle.x - circle.r < e.motion.x && circle.x + circle.r > e.motion.x &&
        circle.y - circle.r < e.motion.y && circle.y + circle.r > e.motion.y) {
        circle.x = e.motion.x;
        circle.y = e.motion.y;
    }
}
```
- Detects when a circle is clicked and updates its position accordingly.

---

## 🛠️ Installation & Setup
### 🔹 Prerequisites
Ensure you have **SDL2** installed. On macOS:
```sh
brew install sdl2
```
On Linux (Debian-based):
```sh
sudo apt install libsdl2-dev
```

### 🔹 Compiling & Running
```sh
gcc -o sdl_bounce main.c -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2
./sdl_bounce
```

---

## 📌 Controls
- **Click & Drag**: Move circles around.
- **Quit**: Close the window.

---

## 🎯 Future Improvements
- ✨ Add more realistic physics (e.g., friction, air resistance).
- 🔄 Enable multiple circles with collision detection.
- 🖼️ Add textures and better rendering for enhanced visuals.

---

## 📜 License
This project is open-source and free to use under the **MIT License**.

🚀 **Enjoy coding and experimenting with SDL2!** 🎮

