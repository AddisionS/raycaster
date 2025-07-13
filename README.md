# 🔺 Raycaster Engine  
*A minimalist 2.5D rendering engine built in pure C with OpenGL (GLUT)*

---

## 🧠 What This Is  
This is a project inspired by early 90s FPS engines like **Wolfenstein 3D**, using the classic **raycasting technique** to simulate a 3D world on a 2D grid.  
No fancy shaders, no engines—just raw math, pixels, and pain.

The core idea?  
Cast rays for each vertical slice of the screen, figure out where they hit a wall, and draw accordingly.  
That’s it. The magic happens when you realize it looks 3D, despite being fundamentally 2D.

This engine is a proof-of-concept for how simple rules, when layered and manipulated just right, can trick your brain into seeing depth.

---

## 📜 A Bit of History  
**Raycasting** exploded into the mainstream with *Wolfenstein 3D* (1992). It was Carmack’s brilliance that led to an engine that could render fast pseudo-3D on low-end hardware.  
No Z-buffer. No polygons. Just 2D maps, trigonometry, and clever optimizations.

The method trades true 3D geometry for speed.  
Rays are shot from the player’s point of view into the game world.  
When a ray hits a wall, the distance is calculated and used to draw a vertical line on the screen — shorter lines for distant walls, taller ones for closer walls.

That simplicity is what makes it beautiful.  
That simplicity is why it's being recreated here, from scratch.

---

## 🕹️ Current Features  
- Manual implementation of raycasting logic  
- Fully controllable player with rotation and strafing  
- Real-time 3D rendering using 2D grid logic  
- Smooth map collisions  
- Overhead 2D map with player direction  
- Basic shading based on hit direction  
- GLUT-powered rendering loop

---

## ⌨️ Controls  
- `w` / `s` — Move forward and backward  
- `a` / `d` — Rotate left and right  
- `q` / `e` — Strafe left and right

---

## 🧱 Tech Stack  
- C99  
- OpenGL (GLUT)  
- Pure math and trigonometry  
- No external game engine

---

## 💡 Future Plans  
- Add texture mapping  
- Colored ceilings and floors  
- Sprite rendering (enemies, pickups)  
- Map editor for easy level creation  
- Dynamic lighting and fog  
- Save/load system

---

## 🛠️ Build Instructions
If using *Dev-C++* to compile the code, do not forget to add the following linker flags:
-lopengl32
-lglu32
-lfreeglut

---

*Built for the love of low-level graphics. A tribute to the legends who did more with less.*
