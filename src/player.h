#pragma once

#include <SFML/Graphics.hpp>

#define MOVE_SPEED 5
#define PLAYER_WIDTH 25 
#define PLAYER_HEIGHT 75

class Application;

class Player
{
public:
    Player(int xPos);
    void render(sf::RenderWindow* window);
    void update();
    void jump();

    int score = 0;
    sf::Vector2f pos;
    Application* parent;
    sf::RectangleShape* m_rect;
private:
    int jumpPos = 0;
    float yAccel = 0;
    bool jumping = false;
};