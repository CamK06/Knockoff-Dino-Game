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
    m_player->parent = this;

    // Graphics setup
    // Initialization hell go b r r r
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
    m_gameOverText->setString("Press space to start");
    m_gameOverText->setCharacterSize(100);
    m_gameOverText->setFillColor(sf::Color::White);
    m_gameOverText->setPosition(WIDTH/2, HEIGHT/2);
    sf::FloatRect textSize = m_gameOverText->getLocalBounds();
    m_gameOverText->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_gameOverText->setPosition(WIDTH/2, HEIGHT/2);
    m_glideBar = new sf::RectangleShape;
    m_glideBar->setPosition(27, 27);
    m_glideBar->setSize(sf::Vector2f(25, 100));
    m_glideBar->setFillColor(sf::Color::Green);
    m_glideBarBg = new sf::RectangleShape;
    m_glideBarBg->setPosition(25, 25);
    m_glideBarBg->setSize(sf::Vector2f(29, 104));
    m_glideBarBg->setFillColor(sf::Color::White);
    

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

    // Game loop
    while(m_window->isOpen()) {
        handleEvents();
        update();
        render();
    }
    return 0;
}

void Application::update()
{
    if(!started)
        return;

    // Update game objects
    m_player->update();
    for(int i = 0; i < obstacles.size(); i++)
        obstacles[i].update();
    updateScore();
    speed += 0.0005f;

    // Adjust the glide bar
    m_glideBar->setSize(sf::Vector2f(25, glidePower));
    if(glidePower < 100)
        m_glideBar->setPosition(27, 27+(100-glidePower));

    // Glide if up is pressed and the player is in the air
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && glidePower > 0
       && m_player->pos.y < HEIGHT-175 && glideRegenned) {
        m_player->yAccel = -4;
        glidePower -= 2;
    }

    // Regenerate glide power
    if(glidePower <= 0)
        glideRegenned = false;
    if(glidePower < 100 && !glideRegenned)
        glidePower += 0.5f;
    else if(glidePower >= 100 && !glideRegenned)
        glideRegenned = true;
}

void Application::render()
{
    m_window->clear(sf::Color::Black);

    // Render UI
    m_window->draw(*m_glideBarBg);
    m_window->draw(*m_glideBar);
    m_window->draw(*m_scoreText);

    // Render player, obstacles and level
    for(int i = 0; i < obstacles.size(); i++)
        m_window->draw(*obstacles[i].rect);
    m_player->render(m_window);
    m_window->draw(*m_floorRect);
    if(!started)
        m_window->draw(*m_gameOverText);

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

    // Reset obstacles
    obstacles.clear();
    for(int i = 0; i < 3; i++) {
        Obstacle newObstacle(i*random(512, 1024));
        newObstacle.parent = this;
        newObstacle.player = m_player;
        obstacles.push_back(newObstacle);
    }

    // Reset player
    m_player->score = 0;
    speed = 10;

    // Reset gliding
    glidePower = 100;
    glideRegenned = true;
    m_glideBar->setPosition(27, 27);
}

void Application::handleEvents()
{
    sf::Event event;
    while(m_window->pollEvent(event)) {
        // When the X is pressed to exit
        if(event.type == sf::Event::Closed)
            m_window->close();

        // Handle keyDown events
        if(event.type == sf::Event::KeyPressed)
            if(event.key.code == sf::Keyboard::Escape)
                m_window->close();
            else if(event.key.code == sf::Keyboard::Space) {
                if(!started) {
                    started = true;
                    m_gameOverText->setString("You suck!\nPress space to restart");
                    sf::FloatRect textSize = m_gameOverText->getLocalBounds();
                    m_gameOverText->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
                    m_gameOverText->setPosition(WIDTH/2, HEIGHT/2);
                }
                m_player->jump();
            }
    }
}

void Application::updateScore()
{
    m_scoreText->setString(std::to_string((int)m_player->score));
    sf::FloatRect textSize = m_scoreText->getLocalBounds();
    m_scoreText->setOrigin(textSize.left + textSize.width/2.0f, textSize.top + textSize.height/2.0f);
    m_scoreText->setPosition(WIDTH/2, 64);
}