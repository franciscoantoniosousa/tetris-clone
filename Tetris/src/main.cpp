
#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iostream>

Game game;
void KeyPressedEvent(sf::Event event);
int main()
{    
    sf::RenderWindow window({ RESIZED_CELL_SIZE * COLUMNS, RESIZED_CELL_SIZE * ROWS }, "TETRIS");
    window.setFramerateLimit(10);

    sf::Text text;
    sf::Font font; 
    font.loadFromFile("./font/Tetris.ttf");
    text.setFont(font);
    text.setString("GAME OVER! \n PRESS ENTER TO RESTART");
    text.setCharacterSize(24);
    text.setPosition({ 0 , RESIZED_CELL_SIZE * ROWS / 2});

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyPressed:
                KeyPressedEvent(event);
            }
        }
        // clear the window
        window.clear();

        // DRAW EVERYTHING PAST THIS POINT
        // Game Update
        if(game.getIsGameOver() == false)
            game.Update(window);
        else {
            window.draw(text);
        }
        window.display();
    }

    return 0;
}

void KeyPressedEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed)
    {
        sf::Vector2f dummy_vector;
        switch (event.key.scancode) {
            case sf::Keyboard::Scan::W:
            case sf::Keyboard::Scan::Up:
                game.RotateBlock();
                break;
            case sf::Keyboard::Scan::A:
            case sf::Keyboard::Scan::Left:
                dummy_vector = { -1,0 };
                game.MoveBlockLeft();
                break;
            case sf::Keyboard::Scan::D:
            case sf::Keyboard::Scan::Right:
                dummy_vector = { 1,0 };
                game.MoveBlockRight();
                break;
            case sf::Keyboard::Scan::S:
            case sf::Keyboard::Scan::Down:
                dummy_vector = { 0,1 };
                game.MoveBlockDown();
                break;
            case sf::Keyboard::Scan::Enter:
                if(game.getIsGameOver())
                    game.Restart();
                break;
        }
    }
}