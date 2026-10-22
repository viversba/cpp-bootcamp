--------------------------------------------------------------------------
C++ Bootcamp - Workshop 4: Space Invaders, Game Programming Patterns
--------------------------------------------------------------------------
Program Specification:
--------------------------------------------------------------------------

In Workshop 3 you refactored Space Invaders using classical Object-Oriented
Programming: an Enemy base class with TankEnemy and ShooterEnemy subclasses,
and vectors of raw pointers allocated and freed with 'new' and 'delete'.

Now imagine you need a new enemy type: an Armored Shooter that has BOTH the
TankEnemy's 3-hit color-changing armor AND the ShooterEnemy's downward
firing, plus a new zig-zag movement pattern. With classical inheritance,
combining TankEnemy and ShooterEnemy leads to the dreaded C++ "diamond
inheritance" problem or duplicated code. Meanwhile, calling 'new' and
'delete' for every single bullet causes constant heap allocations during
gameplay.

In this final workshop you will solve both problems by refactoring your
game to use two foundational Game Programming Patterns:
1. The Object Pool Pattern (BulletPool) to eliminate runtime heap
   allocations for bullets.
2. The Component Pattern (Composition over Inheritance) to build any enemy
   type by mixing and matching modular components on a single Enemy class.

The game must keep all features from Workshop 3, plus the following:
- Zero 'new' or 'delete' calls for bullets during gameplay. All bullets
  are managed by a pre-allocated BulletPool.
- An ImGui debug readout showing how many bullets in the pool are
  currently active (e.g., "Active Bullets: 14 / 200").
- TankEnemy and ShooterEnemy subclasses are removed and replaced by a
  single Enemy class composed of optional components.
- Three enemy archetypes spawned by combining components:
    * Tank Enemy: slow straight movement + 3-HP armor.
    * Shooter Enemy: normal straight movement + 1-HP + downward shooter.
    * Hybrid Elite Enemy (New!): zig-zag movement + 3-HP armor + downward
      shooter.

--------------------------------------------------------------------------
Requirements:
--------------------------------------------------------------------------

1. Object Pool Pattern (BulletPool):
- Update Bullet so it can be constructed in an "inactive" state and
  re-initialized when spawned, for example with an init(pos, velocity,
  fromPlayer) function and a deactivate() function.
- Create a BulletPool class (BulletPool.h / BulletPool.cpp) that owns a
  fixed-size collection of Bullet objects pre-allocated up front (for
  example, std::vector<Bullet> or std::array<Bullet, 200>).
- BulletPool must provide:
    * A spawn(pos, velocity, fromPlayer) function that finds the first
      inactive Bullet in the pool, initializes it, and activates it. If
      all bullets in the pool are active, it simply does nothing.
    * Functions to update and draw all currently active bullets, as well
      as access active bullets for collision checks.
    * A way to query the number of currently active bullets and the total
      pool capacity for the ImGui debug window.
- Game must no longer store std::vector<Bullet*> or call 'new'/'delete'
  for bullets. Pass a reference to BulletPool wherever bullets need to
  be spawned.

2. Component Pattern (Enemy Composition):
- Remove the TankEnemy and ShooterEnemy subclasses. Enemy is no longer an
  abstract base class; it is a single concrete class that owns optional
  components (stored as pointers or smart pointers, where nullptr means
  the enemy does not have that capability).
- Implement three modular component classes:
    * MovementComponent: updates the enemy's position each frame. Must
      support at least two movement behaviors (e.g., StraightDown and
      ZigZag horizontal oscillation).
    * HealthComponent: tracks current and max HP, handles taking damage,
      and determines the enemy's display color based on remaining health.
    * ShooterComponent: tracks a fire cooldown timer and spawns downward
      enemy bullets into the BulletPool when ready.
- Inside Enemy::update(dt, bulletPool), the Enemy simply updates whichever
  components it owns (checking for nullptr if a component is optional,
  such as ShooterComponent).
- Create helper/factory functions (e.g., Enemy::createTank,
  Enemy::createShooter, Enemy::createElite) or constructor setups that
  assemble the three enemy types by attaching the right components.
- Note for advanced students: If you want an extra challenge, you may
  also create a polymorphic Component base class and store a vector of
  components inside Enemy, though explicit component pointers on Enemy
  are recommended for simplicity.

3. ImGui Pool & Spawner Panel:
- In your ImGui debug window, display the current active bullet count vs.
  pool capacity (e.g., "Active Bullets: X / 200").
- Allow tweaking fire rate or spawning extra enemies so you can stress-test
  the BulletPool and watch it recycle bullets in real time.

Code Style:
- Put each new class in its own pair of files (.h and .cpp) and remove
  TankEnemy and ShooterEnemy from your build. Suggested layout:

    src/main.cpp
    src/Vec2.h               src/Vec2.cpp
    src/Player.h             src/Player.cpp
    src/Bullet.h             src/Bullet.cpp
    src/BulletPool.h         src/BulletPool.cpp
    src/MovementComponent.h  src/MovementComponent.cpp
    src/HealthComponent.h    src/HealthComponent.cpp
    src/ShooterComponent.h   src/ShooterComponent.cpp
    src/Enemy.h              src/Enemy.cpp
    src/Game.h               src/Game.cpp

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

Remember: After removing TankEnemy/ShooterEnemy and adding the new pool
and component .cpp files, re-run the first cmake command before building.

--------------------------------------------------------------------------
Order recommendation:
--------------------------------------------------------------------------

1. Copy your Workshop 3 game into branch w4 and verify it builds and runs.
2. Modify Bullet so it has an active/inactive state and an init(...)
   method to reset its position, velocity, and owner flag.
3. Implement BulletPool with a fixed size (e.g., 200 bullets). Replace
   std::vector<Bullet*> in Game, Player, and Enemy with BulletPool.
4. Add the active bullet counter to the ImGui window and verify shooting
   and collisions work without any 'new' or 'delete' for bullets.
5. Implement MovementComponent, HealthComponent, and ShooterComponent.
6. Refactor Enemy into a single concrete class that holds those components
   and deletes them in ~Enemy() (or uses std::unique_ptr).
7. Remove TankEnemy and ShooterEnemy, and spawn the three enemy types
   (Tank, Shooter, and the new Zig-Zag Armored Shooter) by combining
   components.
