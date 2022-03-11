#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "player.h"
#include "obstacle.h"

#define WIDTH 800
#define HEIGHT 600
#define NUM_SPRITES 1

class Obstacle;

class Application
{
public:
    Application();
    int run();
    void gameOver();

    sf::RenderWindow* m_window;
    float speed = 10;
    float glidePower = 100;
    bool glideRegenned = true;
private:
    Player* m_player;
    sf::Font* m_comicSans;
    sf::Text* m_scoreText;
    sf::Text* m_gameOverText;
    sf::RectangleShape* m_floorRect;
    sf::RectangleShape* m_glideBar;
    sf::RectangleShape* m_glideBarBg;
    std::vector<Obstacle> obstacles;

    void update();
    void updateScore();
    void render();
    void handleEvents();
};