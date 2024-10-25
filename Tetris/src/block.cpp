#include "block.hpp"

Block::Block(int figure)
{
    figure *= rand();
    m_id = figure;
    int current_figure = figure % 6;
    m_positions.resize(4);
    switch (current_figure)
    {
    case 0: // O Shape
        m_positions[0] = { COLUMNS / 2 - 1, 0 };
        m_positions[1] = { COLUMNS / 2, 0 };
        m_positions[2] = { COLUMNS / 2, 1 };
        m_positions[3] = { COLUMNS / 2 - 1, 1 };
        m_color = sf::Color(sf::Color::Yellow);
        break;
    case 1: // I Shape
        m_positions[0] = { COLUMNS / 2 - 2, 0 };
        m_positions[1] = { COLUMNS / 2 - 1, 0 };
        m_positions[2] = { COLUMNS / 2, 0 };
        m_positions[3] = { COLUMNS / 2 + 1, 0 };
        m_color = sf::Color(sf::Color::Cyan);
        break;
    case 2: // L Shape
		m_positions[0] = { COLUMNS / 2 - 1, 0 };
		m_positions[1] = { COLUMNS / 2, 0 };
		m_positions[2] = { COLUMNS / 2 + 1, 0 };
		m_positions[3] = { COLUMNS / 2 - 1, 1 };
        m_color = sf::Color({255,140,0}); // orange
        break;
    case 3: // J Shape
        m_positions[0] = { COLUMNS / 2 - 1, 0 };
        m_positions[1] = { COLUMNS / 2 - 1, 1 };
        m_positions[2] = { COLUMNS / 2, 1 };
        m_positions[3] = { COLUMNS / 2 + 1, 1 };
        m_color = sf::Color(sf::Color::Magenta);
        break;
    case 4: // S Shape
        m_positions[0] = { COLUMNS / 2, 0 };
        m_positions[1] = { COLUMNS / 2 + 1, 0 };
        m_positions[2] = { COLUMNS / 2, 1 };
        m_positions[3] = { COLUMNS / 2 - 1, 1 };
        m_color = sf::Color(sf::Color::Red);
        break;
    case 5: // Z Shape
        m_positions[0] = { COLUMNS / 2 - 1, 0 };
        m_positions[1] = { COLUMNS / 2, 0 };
        m_positions[2] = { COLUMNS / 2, 1 };
        m_positions[3] = { COLUMNS / 2 + 1, 1 };
        m_color = sf::Color({ 107,142,35 }); // Grren
        break;
    case 6: // T Shape
        m_positions[0] = { COLUMNS / 2 - 1, 0 };
        m_positions[1] = { COLUMNS / 2, 0 };
        m_positions[2] = { COLUMNS / 2 + 1, 0 };
        m_positions[3] = { COLUMNS / 2 , 1 };
        m_color = sf::Color({ 128,0,128 }); // Purple
        break;
    default:
        break;
    }

    m_is_being_played = true;
}

void Block::Rotate()
{
}

bool Block::MoveDown(std::vector< std::vector<int>>& m_board_matrix)
{
    for (sf::Vector2f& square : m_positions)
    {
        // check if any of the current shape will hit the bottom if so stop
        if (ROWS <= 1 + square.y)
        {
            return false;
        }
        // Check if the current shape is overlapping another shape
        if (m_board_matrix[square.x][square.y + 1] > 0 && m_board_matrix[square.x][square.y + 1] !=  m_id) {
            return false; 
        }
    }

    for (sf::Vector2f& square : m_positions)
    {		
        // Check if it reached the end of the board
        square.y++;
    }
    return true;
}

void Block::MoveLeft(std::vector< std::vector<int>>& m_board_matrix) {
    for (sf::Vector2f& square : m_positions)
    {
        if (0 < 1 - square.x)
            return;

        if (0 != m_board_matrix[square.x - 1][square.y] && m_board_matrix[square.x - 1][square.y] != m_id)
            return;
    }
    for (sf::Vector2f& square : m_positions)
    {
        square.x--;
    }
}

void Block::MoveRight(std::vector< std::vector<int>>& m_board_matrix) {
    for (sf::Vector2f& square : m_positions)
    {
        if (COLUMNS == 1 + square.x)
            return;

        if (0 != m_board_matrix[square.x + 1][square.y] && m_board_matrix[square.x + 1][square.y] != m_id)
            return;
    }
    for (sf::Vector2f& square : m_positions)
    {
        square.x++;
    }
}