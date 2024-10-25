#pragma once

#ifndef TETRIS_GAME_GAME_H
#define TETRIS_GAME_GAME_H

#include <SFML/Graphics.hpp>
#include "global-variables.hpp"
#include "block.hpp"

class Game {
public:
	Game();
	void Update(sf::RenderWindow& window);
	void DrawBoard(sf::RenderWindow& window);
	void GameOver();
	void MoveBlockDown();
	void MoveBlockLeft();
	void MoveBlockRight();
	void ResetMatrix();
	void Restart();
	void RotateBlock();
	void SpawnNewBlock();

	//Getters and Setters
	inline bool& getIsGameOver() { return m_game_over; }

private:
	std::vector<std::vector<int>>  m_board_matrix;
	std::vector<std::shared_ptr<Block>> m_blocks_in_game;
	std::shared_ptr<Block> m_current_block;
	std::vector <std::vector<int>> m_figures;
	bool m_game_over = false;
	unsigned int randomizer_seed;
};

#endif