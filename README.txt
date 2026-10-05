--------------------------------------------------------------------------
C++ Bootcamp - Workshop 2: Space Invaders
--------------------------------------------------------------------------
Program Specification:
--------------------------------------------------------------------------

In this workshop you will build a simple version of the classic game
Space Invaders using C++, SFML and ImGui. A starter skeleton is provided in
src/main.cpp: it already opens a window, runs the game loop and computes the
delta time (dt) for each frame. Build the game on top of it.

The game must have the following features:

Player:
- The player is represented by a triangular shape at the bottom of the screen.
- The player moves using the keyboard arrow keys.
- The player is confined to move only within the bounds of the window.
- The player shoots a bullet upward when the Space key is pressed.

Enemies:
- Enemies spawn at the top of the screen and move toward the player.
- When a bullet hits an enemy, both the bullet and the enemy are destroyed.

Life / Death Cycle:
- If an enemy collides with the player, the player dies.
- After dying, the player must respawn at its starting position so the
    game can continue.

Score:
- Keep a score counter showing how many enemies the player has killed.
- The score must be displayed on the screen at all times while playing.

Misc:
- The 'ESC' key should close the game window.

Code Style:
- You are allowed to use classes and structs of your own if you already know 
    how to use them. However, this is not required: the whole game can be built
    using plain functions and variables only.
- Whichever approach you choose, split your logic into small functions
    (input, update, collisions, drawing) instead of writing everything
    inside main().

--------------------------------------------------------------------------
Collision Detection (Theory):
--------------------------------------------------------------------------

Your game needs two collision checks: bullet vs enemy and enemy vs player.
You don't need exact shape-vs-shape collision for this. The usual trick in
games is to wrap each entity in a simple invisible "collision shape" and
test those shapes against each other instead.

Radial (circle vs circle) collision:
- Give every entity a center position (x, y) and a collision radius r.
- Two circles overlap when the distance between their centers is smaller
    than the sum of their radii:

        dx = x2 - x1
        dy = y2 - y1
        distance = sqrt(dx*dx + dy*dy)

        collision if distance < r1 + r2

- Tip: sqrt() is relatively slow, and you don't need it here. Square
    both sides and compare instead:

        collision if (dx*dx + dy*dy) < (r1 + r2) * (r1 + r2)

- This works for any shape (triangles, circles, polygons) as long as
    you pick a radius that roughly covers it. A collision radius a bit
    smaller than the drawn shape usually feels fairer to the player.

Watch out for the SFML origin:
- By default, an SFML shape's position is the top-left corner of its
    bounding box, not its center. Either call shape.setOrigin(r, r) on
    your shapes so their position IS the center, or add the radius to the
    position before doing the math above.

Checking every pair:
- To find all hits, loop over every bullet and, inside that loop, over
    every enemy (a "nested loop"), and run the check on each pair.
- When a pair collides, mark both as destroyed. Avoid erasing elements
    from a std::vector while you are looping over it; flag them as dead
    and clean up afterwards instead.

Further reading:
- Circle vs circle, with interactive examples (Jeffrey Thompson):
    https://www.jeffreythompson.org/collision-detection/circle-circle.php

--------------------------------------------------------------------------
Building & Running:
--------------------------------------------------------------------------

From the root of the repository:

    cmake -B build -DCMAKE_BUILD_TYPE=Release

    # Linux / macOS
    cmake --build build
    ./build/SpaceDefender

    # Windows
    cmake --build build --config Release
    .\build\Release\SpaceDefender.exe

--------------------------------------------------------------------------
Order recommendation:
--------------------------------------------------------------------------

1. Build and run the starter skeleton to make sure your environment works.
2. Draw the player on the screen as a simple shape.
3. Implement player movement with the arrow keys, and keep the player
    inside the window.
4. Handle the 'ESC' key to close the window.
5. Implement shooting with the Space key: spawn bullets and move them up.
    Remove bullets once they leave the screen.
6. Spawn enemies at the top of the screen and move them down. Remove
    enemies once they leave the screen.
7. Implement bullet vs enemy collisions and destroy both on a hit.
8. Add the score counter and display it on the screen.
9. Implement player vs enemy collisions and the death / respawn cycle.
