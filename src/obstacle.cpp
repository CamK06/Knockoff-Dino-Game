#include "obstacle.h"
#include "util.h"

Obstacle::Obstacle(int startX)
{
    rect = new sf::RectangleShape;
    rect->setSize(sf::Vector2f(25, 50));
    rect->setPosition(sf::Vector2f(WIDTH + 25 + startX, HEIGHT - 100 - rect->getSize().y));
    rect->setFillColor(sf::Color::White);
    pos = rect->getPosition();
    resetDist = random(128, 256);
    rect->setFillColor(sf::Color(random(0, 255), random(0, 255), random(0, 255)));
}

void Obstacle::update()
{
    pos.x -= parent->speed;
    if (pos.x + 25 <= 0-resetDist) {
        pos.x = WIDTH + 25;
        resetDist = random(256, 1024);
        rect->setFillColor(sf::Color(random(0, 255), random(0, 255), random(0, 255)));
    }
    rect->setPosition(pos);

    if (player->pos.x + PLAYER_WIDTH >= pos.x && player->pos.x <= pos.x + 25 && 
        player->pos.y + PLAYER_HEIGHT >= pos.y) {
        parent->gameOver();
    }
}