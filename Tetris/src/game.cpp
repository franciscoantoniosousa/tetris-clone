#include "game.hpp"


Game::Game() 
{
    randomizer_seed = time(NULL);
    srand(randomizer_seed);
    // Set the board matrix columns to COLUMNS size
    m_board_matrix.resize(COLUMNS);
    for (int col = 0; col < m_board_matrix.size(); col++)
    {
        //  Set the number of rows per column to be ROWS size
        m_board_matrix[col].resize(ROWS);
    }

    // Create the first block in the game
    m_current_block = std::make_shared<Block>(rand());
    m_blocks_in_game.emplace_back(m_current_block);
    ResetMatrix();
}

void Game::DrawBoard(sf::RenderWindow& window)
{
    // Create a dummy cell
    sf::RectangleShape dummy_cell(sf::Vector2f(RESIZED_CELL_SIZE - 2, RESIZED_CELL_SIZE - 2));

    // Create a grid that will make up the game board
    for (int column = 0; column < COLUMNS; column++) {
        for (int row = 0; row < ROWS; row++) {
            // Set dummy_cell to a different position
            dummy_cell.setPosition(RESIZED_CELL_SIZE * column, RESIZED_CELL_SIZE * row);
            // check if the current cell block is part of any shape and set the color properly
            if (m_board_matrix[column][row] == 0) {
                dummy_cell.setFillColor(sf::Color(75, 0, 200));
                window.draw(dummy_cell);
            }
        }
    }

    // draw the blocks in the board
    for (const auto block : m_blocks_in_game) {
        for (const auto square : block->getBlockPositions()) {
            dummy_cell.setPosition(RESIZED_CELL_SIZE * square.x, RESIZED_CELL_SIZE * square.y);
            dummy_cell.setFillColor(block->getColor());
            window.draw(dummy_cell);
        }
    }
}

void Game::GameOver()
{
    m_game_over = true;
}

void Game::MoveBlockDown()
{
    m_current_block->MoveDown(m_board_matrix);
}

void Game::MoveBlockLeft()
{
    m_current_block->MoveLeft(m_board_matrix);
}

void Game::MoveBlockRight()
{
    m_current_block->MoveRight(m_board_matrix);
}

void Game::ResetMatrix()
{
    // reset the board
    for (int column = 0; column < COLUMNS; column++) {
        for (int row = 0; row < ROWS; row++) {
            m_board_matrix[column][row] = 0;
        }
    }

    //  set the current positions of each block
    for (const auto block : m_blocks_in_game) {
        for (const auto position : block->getBlockPositions()) {
            m_board_matrix[position.x][position.y] = block->getId();
        }
    }
}

void Game::Restart()
{
    m_game_over = false;
    m_blocks_in_game.clear();
    
    // Create the first block in the game
    m_current_block = std::make_shared<Block>(rand());
    m_blocks_in_game.emplace_back(m_current_block);
    ResetMatrix();
}

void Game::RotateBlock()
{
    m_current_block->Rotate();
}

void Game::SpawnNewBlock()
{
    // check if the curretn block is being played
    if ( m_current_block->getIsBeingPlayed())
        return;
    //Check if its game over
    for (sf::Vector2f& square : m_current_block->getBlockPositions())
    {
        if (square.y == 0) {
            GameOver();
        }
    }

    // create a new one block if the last block reach the end
    m_current_block = std::make_shared<Block>(rand());
    m_blocks_in_game.emplace_back(m_current_block);
}

void Game::Update(sf::RenderWindow& window)
{
    ResetMatrix();
    DrawBoard(window);
    m_current_block->setIsBeingPlayed(m_current_block->MoveDown(m_board_matrix));
    SpawnNewBlock();
}
