#include "player.h"
#include "application.h"

#include <iostream>

Player::Player(int xPos = 50)
{
    m_rect = new sf::RectangleShape();
    m_rect->setFillColor(sf::Color::Black);
    m_rect->setPosition(sf::Vector2f(50, HEIGHT-100-PLAYER_HEIGHT));
    m_rect->setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));

    m_dinoTex = new sf::Texture;
    m_dinoTex->loadFromFile("res/dino.png");
    m_rect->setTexture(m_dinoTex);

    pos.x = xPos;
    pos.y = HEIGHT-100-PLAYER_HEIGHT;
    yAccel = 10;
}

void Player::render(sf::RenderWindow* window)
{
    window->draw(*m_rect);
}

void Player::jump()
{
    if(pos.y == HEIGHT-100-PLAYER_HEIGHT)
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
    if(pos.y > HEIGHT-100-PLAYER_HEIGHT)
        pos.y = HEIGHT-100-PLAYER_HEIGHT;
    
    score++;
    if(parent != nullptr)
        score += parent->speed/4;
    m_rect->setPosition(pos);
}