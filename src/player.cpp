#include "player.h"
#include "application.h"

#include <iostream>

Player::Player(int xPos = 50)
{
    m_rect = new sf::RectangleShape();
    m_rect->setFillColor(sf::Color::White);
    m_rect->setPosition(sf::Vector2f(10, HEIGHT/2));
    m_rect->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));

    pos.x = xPos;
    pos.y = HEIGHT/2;
    yAccel = 10;
}

void Player::render(sf::RenderWindow* window)
{
    window->draw(*m_rect);
}

void Player::jump()
{
    if(pos.y == HEIGHT-175)
        yAccel = -8;
}

void Player::update()
{
    // Apply gravity/jump force
    pos.y += yAccel;
    yAccel += 0.40;

    // Fast descend
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        yAccel += 1.5;

    // Floor collision
    if(pos.y > HEIGHT-175)
        pos.y = HEIGHT-175;
    
    score++;
    m_rect->setPosition(pos);
}