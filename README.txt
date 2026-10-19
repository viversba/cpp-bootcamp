--------------------------------------------------------------------------
C++ Bootcamp - Workshop 3: Space Invaders, the OOP Rewrite
--------------------------------------------------------------------------
Program Specification:
--------------------------------------------------------------------------

In Workshop 2 you built Space Invaders using functions and variables. In
this workshop you will rewrite that same game using classes, inheritance,
polymorphism, pointers and operator overloading, while extending the
gameplay with two distinct enemy types and weapon switching.

When you are done, the code behind your game should be organized into
objects that each own their own data and behavior, using a base Enemy
class for shared enemy logic and derived classes for specific behaviors.

The game must keep all the features from Workshop 2, plus the new
gameplay additions:
- The player is a triangular shape at the bottom of the screen.
- The player moves with the arrow keys and stays inside the window.
- The player shoots when the Space key is pressed and can switch between
  two weapon modes: Single Shot and Triple Spread Shot.
- Two types of enemies spawn at the top of the screen and move toward
  the player:
    * TankEnemy: larger, moves slower, takes 3 hits to destroy, and
      changes color as its health decreases.
    * ShooterEnemy: takes 1 hit to destroy and periodically fires
      bullets downward at the player.
- When a player bullet hits an enemy, the bullet is destroyed and the
  enemy takes damage (and is destroyed when its health reaches 0).
- If an enemy or an enemy bullet collides with the player, the player
  dies and respawns at its starting position.
- A score counter with the number of enemies killed is always visible.
- The 'ESC' key closes the game window.

--------------------------------------------------------------------------
Requirements:
--------------------------------------------------------------------------

Vec2 class (operator overloading):
- Create a Vec2 class that holds two floats, x and y.
- Use Vec2 for every position and velocity in the game. No more separate
  x and y variables.
- Vec2 must overload at least the following operators:
    +   Vec2 + Vec2   returns a new Vec2
    -   Vec2 - Vec2   returns a new Vec2
    *   Vec2 * float  returns a new Vec2 (scales the vector)
    +=  Vec2 += Vec2  modifies the left Vec2
    ==  Vec2 == Vec2  returns true if both x and y are equal
- Vec2 must also have a length() member function that returns the
  length of the vector: sqrt(x*x + y*y).
- Your collision code should use Vec2. For example, the distance between
  two entities is just (b.pos - a.pos).length().

Game entity classes (inheritance and polymorphism):
- Create a Player class, a Bullet class, an abstract Enemy base class,
  and two derived enemy classes: TankEnemy and ShooterEnemy.
- Each class must have:
    * Its data (position, velocity, collision radius, shape, etc.) kept
      private or protected.
    * A constructor that sets it up in a valid starting state.
    * Public member functions for what it does, for example update(dt),
      draw(window) and isAlive().
- Each class keeps its own sf::Shape and is responsible for drawing
  itself.
- Player weapon upgrades:
    * The player must be able to switch between Single Shot (fires 1
      bullet straight up) and Triple Spread Shot (fires 3 bullets at
      once: one straight up, one diagonally left, and one diagonally
      right), for example using the '1' and '2' keys or ImGui.
- Bullet class:
    * Uses a Vec2 velocity so it can travel straight up, diagonally, or
      downward.
    * Tracks whether it was fired by the player or an enemy so collision
      checks know what it can hit.
- Enemy hierarchy:
    * Enemy must be an abstract base class with a virtual destructor
      (virtual ~Enemy()) and a pure virtual update function.
    * TankEnemy inherits from Enemy, starts with 3 health points, moves
      slower, and updates its color each time it takes damage.
    * ShooterEnemy inherits from Enemy, starts with 1 health point, and
      periodically spawns downward-moving enemy bullets.

Game class:
- Create a Game class that owns the window, the player, the enemies, the
  bullets and the score.
- It should have one public function, run(), that contains the game
  loop. Inside run(), split the work into private member functions,
  for example handleInput(), update(dt), checkCollisions() and render().
- Your main() should become very small: create a Game and call run().

Pointers and memory:
- Store enemies and bullets as pointers created with 'new':

    std::vector<Enemy*> m_enemies;
    std::vector<Bullet*> m_bullets;

- Because m_enemies holds base class pointers (Enemy*), it can store
  both new TankEnemy(...) and new ShooterEnemy(...) instances.
- When an enemy or bullet dies, you must 'delete' it and remove its
  pointer from the vector.
- The Game destructor must delete every enemy and bullet that is still
  alive when the window closes.
- Your program must not leak memory. Every 'new' needs exactly one
  matching 'delete'.

Code Style:
- Put each class in its own pair of files: a header (.h) with the class
  declaration and a source file (.cpp) with the member function
  definitions. Suggested layout:

    src/main.cpp
    src/Vec2.h          src/Vec2.cpp
    src/Player.h        src/Player.cpp
    src/Enemy.h         src/Enemy.cpp
    src/TankEnemy.h     src/TankEnemy.cpp
    src/ShooterEnemy.h  src/ShooterEnemy.cpp
    src/Bullet.h        src/Bullet.cpp
    src/Game.h          src/Game.cpp

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

Remember: CMake only picks up new .cpp files when it re-configures. After
adding a new file, run the first cmake command again before building.

--------------------------------------------------------------------------
Order recommendation:
--------------------------------------------------------------------------

1. Copy your Workshop 2 game into this branch and make sure it still
   builds and runs.
2. Implement the Vec2 class and its operators. Test it with a few quick
   prints in main() before using it in the game.
3. Replace every x/y pair in your game with a Vec2. Run the game: it
   should still play exactly the same.
4. Create the Player class and move all the player logic into it.
5. Create the Bullet class using a Vec2 velocity. Store bullets as
   Bullet* in a vector, and delete the ones that leave the screen.
6. Add weapon switching to Player so it can fire either a Single Shot
   or a Triple Spread Shot.
7. Create the abstract Enemy base class, then implement TankEnemy and
   ShooterEnemy as derived classes.
8. Move the collision checks so they use the classes, Vec2, and handle
   both player bullets hitting enemies and enemy bullets hitting the
   player.
9. Create the Game class, move the game loop into Game::run(), and
   shrink main() down to creating a Game and calling run().
10. Write the Game destructor and double check that every 'new' has a
    matching 'delete' (and that Enemy has a virtual destructor).
