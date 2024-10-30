#include "tetromino.hpp"

Tetromino::Tetromino(int figure)
{
	figure *= rand();
	m_id = figure;
	int current_figure = figure % 7;
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
		m_positions[0] = { COLUMNS / 2 - 1, 1 };
		m_positions[1] = { COLUMNS / 2, 1 };
		m_positions[2] = { COLUMNS / 2 + 1, 1 };
		m_positions[3] = { COLUMNS / 2 + 1, 0 };
		m_color = sf::Color({ 255,140,0 }); // orange
		break;
	case 3: // J Shape
		m_positions[0] = { COLUMNS / 2 - 1, 0 };
		m_positions[1] = { COLUMNS / 2 - 1, 1 };
		m_positions[2] = { COLUMNS / 2, 1 };
		m_positions[3] = { COLUMNS / 2 + 1, 1 };
		m_color = sf::Color(sf::Color::Magenta);
		break;
	case 4: // S Shape
		m_positions[0] = { COLUMNS / 2 + 1, 0 };
		m_positions[1] = { COLUMNS / 2, 0 };
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
		m_positions[0] = { COLUMNS / 2, 0 };
		m_positions[1] = { COLUMNS / 2 - 1, 1 };
		m_positions[2] = { COLUMNS / 2, 1 };
		m_positions[3] = { COLUMNS / 2 + 1, 1 };
		m_color = sf::Color({ 128,0,128 }); // Purple
		break;
	default:
		break;
	}

	m_is_being_played = true;
}

std::vector<sf::Vector2f> Tetromino::Rotate()
{
	if (m_move_down_count < 1) {
		return m_positions;
	}

	int current_figure = m_id % 7;
	int rotation_id = ++m_current_rotation % 4;
	std::vector<sf::Vector2f> dummy_tetromino = m_positions;
	switch (current_figure)
	{
	case 0: // O Shape
		dummy_tetromino[0] += { 0, 0};
		dummy_tetromino[1] += { 0, 0 };
		dummy_tetromino[2] += { 0, 0};
		dummy_tetromino[3] += { 0, 0 };
		break;
	case 1: // I Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { -1, -2 };
			dummy_tetromino[1] += { 0, -1};
			dummy_tetromino[2] += { 1, 0};
			dummy_tetromino[3] += { 2, 1 };
			break;
		case 1:
			dummy_tetromino[0] += { 2, -1 };
			dummy_tetromino[1] += { 1, 0 };
			dummy_tetromino[2] += { 0, 1};
			dummy_tetromino[3] += { -1, 2 };
			break;
		case 2:
			dummy_tetromino[0] += { 1, 2 };
			dummy_tetromino[1] += { 0, 1 };
			dummy_tetromino[2] += { -1, 0};
			dummy_tetromino[3] += { -2, -1 };
			break;
		case 3:
			dummy_tetromino[0] += { -2, 1 };
			dummy_tetromino[1] += { -1, 0 };
			dummy_tetromino[2] += { 0, -1};
			dummy_tetromino[3] += { 1, -2 };
			break;
		}
		break;
	case 2: // L Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { -1, -1 };
			dummy_tetromino[1] += { 0, 0 };
			dummy_tetromino[2] += { 1, 1};
			dummy_tetromino[3] += { 2, 0 };
			break;
		case 1:
			dummy_tetromino[0] += { 1, -1 };
			dummy_tetromino[1] += { 0, 0 };
			dummy_tetromino[2] += { -1, 1};
			dummy_tetromino[3] += { 0, 2 };
			break;
		case 2:
			dummy_tetromino[0] += { 1, 1 };
			dummy_tetromino[1] += { 0, 0 };
			dummy_tetromino[2] += { -1, -1};
			dummy_tetromino[3] += { -2, 0};
			break;
		case 3:
			dummy_tetromino[0] += { -1, 1 };
			dummy_tetromino[1] += { 0, 0 };
			dummy_tetromino[2] += { 1, -1};
			dummy_tetromino[3] += { 0, -2 };
			break;
		}
		break;
	case 3: // J Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { 0, -2 };
			dummy_tetromino[1] += { -1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, 1 };
			break;
		case 1:
			dummy_tetromino[0] += { 2, 0 };
			dummy_tetromino[1] += { 1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, 1 };;
			break;
		case 2:
			dummy_tetromino[0] += { 0, 2 };
			dummy_tetromino[1] += { 1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, -1 };
			break;
		case 3:
			dummy_tetromino[0] += { -2, 0 };
			dummy_tetromino[1] += { -1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, -1 };
			break;
		}
		break;
	case 4: // S Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { 2, 0 };
			dummy_tetromino[1] += { 1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, -1 };
			break;
		case 1:
			dummy_tetromino[0] += { 0, 2 };
			dummy_tetromino[1] += { 1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, -1 };;
			break;
		case 2:
			dummy_tetromino[0] += { -2, 0 };
			dummy_tetromino[1] += { -1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, 1 };
			break;
		case 3:
			dummy_tetromino[0] += { 0, -2 };
			dummy_tetromino[1] += { -1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, 1 };
			break;
		}
		break;
	case 5: // Z Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { 0, -2 };
			dummy_tetromino[1] += { 1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, 1 };
			break;
		case 1:
			dummy_tetromino[0] += { 2, 0 };
			dummy_tetromino[1] += { 1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, 1 };;
			break;
		case 2:
			dummy_tetromino[0] += { 0, 2 };
			dummy_tetromino[1] += { -1, 1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { -1, -1 };
			break;
		case 3:
			dummy_tetromino[0] += { -2, 0 };
			dummy_tetromino[1] += { -1, -1 };
			dummy_tetromino[2] += { 0, 0}; // origin point
			dummy_tetromino[3] += { 1, -1 };
			break;
		}
		break;
	case 6: // T Shape
		switch (rotation_id)
		{
		case 0:
			dummy_tetromino[0] += { 1, -1 };
			dummy_tetromino[1] += { -1, -1 };
			dummy_tetromino[2] += { 0, 0};
			dummy_tetromino[3] += { 1, 1 };
			break;
		case 1:
			dummy_tetromino[0] += { 1, 1 };
			dummy_tetromino[1] += { 1, -1 };
			dummy_tetromino[2] += { 0, 0};
			dummy_tetromino[3] += { -1, 1 };;
			break;
		case 2:
			dummy_tetromino[0] += { -1, 1 };
			dummy_tetromino[1] += { 1, 1 };
			dummy_tetromino[2] += { 0, 0};
			dummy_tetromino[3] += { -1, -1 };
			break;
		case 3:
			dummy_tetromino[0] += { -1, -1 };
			dummy_tetromino[1] += { -1, 1 };
			dummy_tetromino[2] += { 0, 0};
			dummy_tetromino[3] += { 1, -1 };
			break;
		}
		break;
	default:
		break;
	}

	for (auto& square : dummy_tetromino) {
		if (square.x < 0) {
			dummy_tetromino[0].x += 1;
			dummy_tetromino[1].x += 1;
			dummy_tetromino[2].x += 1;
			dummy_tetromino[3].x += 1;
			break;
		}
		if (square.x > COLUMNS - 1) {
			dummy_tetromino[0].x -= 1;
			dummy_tetromino[1].x -= 1;
			dummy_tetromino[2].x -= 1;
			dummy_tetromino[3].x -= 1;
			break;
		}
		if (square.y > ROWS - 1) {
			dummy_tetromino[0].y -= 1;
			dummy_tetromino[1].y -= 1;
			dummy_tetromino[2].y -= 1;
			dummy_tetromino[3].y -= 1;
			break;
		}
	}

	return dummy_tetromino;
}

std::vector<sf::Vector2f> Tetromino::MoveDown()
{
	std::vector<sf::Vector2f> dummy_tetromino = m_positions;	

	for (sf::Vector2f& square : dummy_tetromino)
	{
		// Check if it reached the end of the board
		square.y++;

	}
	m_move_down_count++;
	if (m_move_down_count > 0) {
		m_can_drop = true;
	}
	return dummy_tetromino;
}

std::vector<sf::Vector2f> Tetromino::MoveLeft() {
	m_can_move = false;

	std::vector<sf::Vector2f> dummy_tetromino = m_positions;
	for (sf::Vector2f& square : dummy_tetromino)
	{
		square.x--;
	}
	m_can_move = true;
	return dummy_tetromino;
}

std::vector<sf::Vector2f> Tetromino::MoveRight() {
	m_can_move = false;
	std::vector<sf::Vector2f> dummy_tetromino = m_positions;
	for (sf::Vector2f& square : dummy_tetromino)
	{
		square.x++;
	}
	m_can_move = true;
	return dummy_tetromino;
}