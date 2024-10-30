
#pragma once
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <iostream>

Game game;
void CheckKeyboardEvents();

int main()
{
    sf::RenderWindow window({ RESIZED_CELL_SIZE * COLUMNS + 400, RESIZED_CELL_SIZE * ROWS }, "TETRIS");
    game.setWindow(&window);
    window.setFramerateLimit(30);
    int framecount = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyPressed:
                CheckKeyboardEvents();
            }
        }

        // clear the window
        window.clear();

        // DRAW EVERYTHING PAST THIS POINT
        // Game Update
        if (game.getIsGameOver() == false)
        {
            game.Update(framecount % 15== 0);
        }
        window.display();
        framecount++;
    }
}

void CheckKeyboardEvents()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        game.RotateTetromino();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        game.MoveTetrominoDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        game.MoveTetrominoLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        game.MoveTetrominoRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(game.CanDrop())
        {
            game.DropTetromino();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (game.getIsGameOver())
            game.Restart();
    }
}
