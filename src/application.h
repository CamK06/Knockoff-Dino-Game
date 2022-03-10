#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "obstacle.h"

#define WIDTH 1280
#define HEIGHT 720
#define NUM_SPRITES 1

class Obstacle;

class Application
{
public:
    Application();
    int run();
    void gameOver();

    sf::RenderWindow* m_window;
    int speed = 10;
private:
    Player* m_player;
    sf::Font* m_comicSans;
    sf::Text* m_scoreText;
    sf::Text* m_gameOverText;
    sf::RectangleShape* m_floorRect;
    std::vector<Obstacle> obstacles;

    void update();
    void updateScore();
    void render();
    void handleEvents();
};