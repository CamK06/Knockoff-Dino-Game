#pragma once

#include <SFML/Graphics.hpp>
#include "application.h"

class Application;

class Obstacle
{
public:
    Obstacle(int startX);
    void update();
    void render();

    Application* parent;
    sf::RectangleShape* rect;
    sf::Texture* tex;
    Player* player;
private:
    sf::Vector2f pos;
    int resetDist = 0;
};