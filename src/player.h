#pragma once

#include <SFML/Graphics.hpp>

#define MOVE_SPEED 5
#define PLAYER_WIDTH 55.3
#define PLAYER_HEIGHT 60

class Application;

class Player
{
public:
    Player(int xPos);
    void render(sf::RenderWindow* window);
    void update();
    void jump();

    float score = 0;
    sf::Vector2f pos;
    Application* parent;
    sf::RectangleShape* m_rect;
    sf::Texture* m_dinoTex;
    float yAccel = 0;
private:
    int jumpPos = 0;
    bool jumping = false;
};