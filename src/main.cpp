// Space Defender - starter skeleton.

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Defender");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window)) {
        return -1;
    }

    sf::Clock deltaClock;

    // TODO: declare your game state here (player, enemies, projectiles, score)

    while (window.isOpen()) {
        // 1. Events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 2. Timing
        const sf::Time dt_time = deltaClock.restart();
        const float dt = dt_time.asSeconds();
        (void)dt; // simple example of how to get a valid DeltaTime for your game

        ImGui::SFML::Update(window, dt_time);

        // 3. Update logic
        // TODO: 
        //   * player input 
        //   * enemy spawning
        //   * movement
        //   * collisions

        // 4. Draw logic
        window.clear(sf::Color(10, 10, 30));
        // TODO: draw the game and the ImGui "Dev Panel"
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
