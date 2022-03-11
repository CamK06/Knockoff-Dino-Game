#include "obstacle.h"
#include "util.h"

Obstacle::Obstacle(int startX)
{
    rect = new sf::RectangleShape;
    rect->setSize(sf::Vector2f(30, 50));
    rect->setPosition(sf::Vector2f(WIDTH + 25 + startX, HEIGHT - 100 - rect->getSize().y));
    rect->setFillColor(sf::Color::Black);
    pos = rect->getPosition();
    resetDist = random(256, 2048);
    tex = new sf::Texture;
    tex->loadFromFile("res/cacti.png");
    rect->setTexture(tex);
}

void Obstacle::update()
{
    pos.x -= parent->speed;
    if (pos.x + 30 <= 0-resetDist) {
        pos.x = WIDTH + 30;
        resetDist = random(256, 1024);
    }
    rect->setPosition(pos);

    if (player->pos.x + PLAYER_WIDTH >= pos.x && player->pos.x <= pos.x + 30 && 
        player->pos.y + PLAYER_HEIGHT >= pos.y) {
        parent->gameOver();
    }
}