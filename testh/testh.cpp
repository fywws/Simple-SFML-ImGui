#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/Shader.hpp>

#include "SFML/Graphics.hpp"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Window Title", sf::Style::Fullscreen);
    ImGui::SFML::Init(window);

    float radius = 10;
    float velocity = 5;

    sf::CircleShape shape(radius, 40);
    shape.setPosition(960, 540);

    bool isDragging = false;  // Flag to track if the shape is being dragged
    sf::Vector2f offset;      // Offset to move the shape based on cursor position





    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
                if (shape.getGlobalBounds().contains(mousePos))
                {
                    isDragging = true;
                    offset = shape.getPosition() - mousePos;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = false;
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // Move the shape if it's being dragged
        if (isDragging)
        {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            shape.setPosition(mousePos + offset);
        }


        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::SliderFloat("Test", &radius, 1.f, 300.f);
        // Color picker for the shape
        ImGui::End();

        shape.setRadius(radius);

        window.clear(sf::Color(18, 33, 43));
        window.draw(shape);
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}