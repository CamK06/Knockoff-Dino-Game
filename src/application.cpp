#include "application.h"
#include "util.h"
#include "player.h"

#include <chrono>
#include <thread>

Application::Application()
{
    // Window setup
    m_window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Cheap Chinese Knockoff Dino Game");
    m_window->setFramerateLimit(60);

    // Game setup
    m_player = new Player(50);

    // Graphics setup
    m_comicSans = new sf::Font;
    m_comicSans->loadFromFile("res/ComicSans.ttf");
    m_scoreText = new sf::Text;
    m_scoreText->setFont(*m_comicSans);
    m_scoreText->setString("0");
    m_scoreText->setCharacterSize(96);
    m_scoreText->setFillColor(sf::Color::White);
    m_scoreText->setPosition(WIDTH/2, 32);
    m_floorRect = new sf::RectangleShape;
    m_floorRect->setPosition(0, HEIGHT-100);
    m_floorRect->setFillColor(sf::Color(128, 128, 128));
    m_floorRect->setSize(sf::Vector2f(WIDTH, 100));
    updateScore();
    m_gameOverText = new sf::Text;
    m_gameOverText->setFont(*m_comicSans);
    m_gameOverText->setString("You suck!\nPress space to restart");
    m_gameOverText->setCharacterSize(100);
    m_gameOverText->setFillColor(sf::Color::White);
    m_gameOverText->setPosition(WIDTH/2, HEIGHT/2);
    sf::FloatRect textSize = m_gameOverText->getLocalBounds();
    m_gameOverText->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_gameOverText->setPosition(WIDTH/2, HEIGHT/2);

    // Initialize obstacles
    for(int i = 0; i < 3; i++) {
        Obstacle newObstacle(i*random(512, 1024));
        newObstacle.parent = this;
        newObstacle.player = m_player;
        obstacles.push_back(newObstacle);
    }
}

int Application::run()
{
    while(m_window->isOpen()) {
        handleEvents();
        update();
        render();
    }
    return 0;
}

void Application::update()
{
    // Update game objects
    m_player->update();
    for(int i = 0; i < obstacles.size(); i++)
        obstacles[i].update();
    updateScore();
}

void Application::render()
{
    m_window->clear(sf::Color::Black);
    for(int i = 0; i < obstacles.size(); i++)
        m_window->draw(*obstacles[i].rect);
    m_window->draw(*m_scoreText);
    m_player->render(m_window);
    m_window->draw(*m_floorRect);
    m_window->display();
}

void Application::gameOver()
{
    // This code isn't great but it works
    updateScore();
    for(int i = 0; i < 3; i++) {
        m_player->m_rect->setFillColor(sf::Color::White);
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        m_player->m_rect->setFillColor(sf::Color::Black);
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    m_player->m_rect->setFillColor(sf::Color::White);
    render();

    // Game over loop (this sucks but whatever)
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_window->draw(*m_gameOverText);
        m_window->display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            exit(0);
    }

    obstacles.clear();
    m_player->score = 0;
    for(int i = 0; i < 3; i++) {
        Obstacle newObstacle(i*random(512, 1024));
        newObstacle.parent = this;
        newObstacle.player = m_player;
        obstacles.push_back(newObstacle);
    }
}

void Application::handleEvents()
{
    sf::Event event;
    while(m_window->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            m_window->close();
        if(event.type == sf::Event::KeyPressed)
            if(event.key.code == sf::Keyboard::Escape)
                m_window->close();
            else if(event.key.code == sf::Keyboard::Space)
                m_player->jump();
    }
}

void Application::updateScore()
{
    m_scoreText->setString(std::to_string(m_player->score));
    sf::FloatRect textSize = m_scoreText->getLocalBounds();
    m_scoreText->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_scoreText->setPosition(WIDTH/2, 64);
}