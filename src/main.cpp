#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"

int main() {
    // 1. Create the application window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bootcamp Workshop 1: Environment Verification");
    window.setFramerateLimit(60);

    // 2. Initialize the ImGui-SFML binding
    if (!ImGui::SFML::Init(window)) {
        return -1; // Initialization failed
    }

    sf::Clock deltaClock;

    // 3. Application Main Loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Forward window events to ImGui
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update ImGui frame state
        ImGui::SFML::Update(window, deltaClock.restart());

        // 4. Construct the ImGui Diagnostic Interface
        ImGui::Begin("Verification Panel");
        
        ImGui::Text("If you can see this window, environment setup was successful!");
        ImGui::Separator();

        static float backgroundColor[3] = { 0.1f, 0.1f, 0.1f };
        ImGui::ColorEdit3("Window Background Color", backgroundColor);

        static int clickCount = 0;
        if (ImGui::Button("Click Me")) {
            clickCount++;
        }
        ImGui::SameLine();
        ImGui::Text("Click Count: %d", clickCount);

        ImGui::End();

        // 5. Render Processing
        sf::Color clearColor(
            static_cast<sf::Uint8>(backgroundColor[0] * 255),
            static_cast<sf::Uint8>(backgroundColor[1] * 255),
            static_cast<sf::Uint8>(backgroundColor[2] * 255)
        );
        window.clear(clearColor);

        // Render the ImGui draw layers over the SFML scene
        ImGui::SFML::Render(window);
        window.display();
    }

    // 6. Resource Cleanup
    ImGui::SFML::Shutdown();

    return 0;
}
