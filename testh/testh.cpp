#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics/Shader.hpp>

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Window Title", sf::Style::Default);
    ImGui::SFML::Init(window);

    float radius = 10;
    float velocity = 5;
    ImColor color(255, 255, 255);
    ImColor bgColor(148, 100, 130);


    sf::CircleShape* shape = new sf::CircleShape(radius, 40);
    shape->setPosition(960, 540);
    shape->setFillColor(sf::Color(color));

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
                if (shape->getGlobalBounds().contains(mousePos))
                {
                    isDragging = true;
                    offset = shape->getPosition() - mousePos;
                }
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                isDragging = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
            {
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // Move the shape if it's being dragged
        if (isDragging)
        {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            shape->setPosition(mousePos + offset);
        }


        ImGui::Begin("Shape edit");
        ImGui::SliderFloat("Radius", &radius, 1.f, 300.f);
        ImGui::ColorEdit4("Color", (float*)&color);
        // Color picker for the shape
        ImGui::End();

        ImGui::Begin("Render");
        ImGui::ColorEdit4("Color", (float*)&bgColor);

        ImGui::End();

        shape->setRadius(radius);
        shape->setFillColor(sf::Color(color));
        window.clear(sf::Color(bgColor));
        window.draw(*shape);
        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}