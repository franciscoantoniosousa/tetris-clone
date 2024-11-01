#pragma once

#ifndef TETRIS_GAME_GAME_H
#define TETRIS_GAME_GAME_H

#include <SFML/Graphics.hpp>
#include "global-variables.hpp"
#include "tetromino.hpp"

class Game {
public:
	Game();
	void Update(bool drop_block);
	bool CanTetrominoMove(std::vector<sf::Vector2f> current_tetromino);
	bool CanTetrominoMoveDown(std::vector<sf::Vector2f> dummy_tetromino);
	void DrawBoard();
	void DropTetromino();
	void GameOver();
	sf::Color GetTetrominoColor(int block_id);
	void MoveTetrominoDown(std::shared_ptr<Tetromino>& tetromino, bool count_score = true);
	void MoveTetrominoLeft();
	void MoveTetrominoRight();
	void ResetMatrix();
	void Restart();
	void RotateTetromino();
	void ScanBoard();
	void ScoreRow(int row);
	void setWindow(sf::RenderWindow *window) { if (m_window == nullptr) m_window = window; }
	void SpawnNewBlock();

	//Getters and Setters
	inline bool& CanDrop() { return m_current_tetromino->getCanDrop(); }
	inline bool& getIsGameOver() { return m_game_over; }
	inline std::shared_ptr<Tetromino>& getCurrentTetromino() { return m_current_tetromino; }
	inline int& getLevel() { return m_level; }

private:
	std::vector<std::vector<int>>  m_board_matrix;
	std::shared_ptr<Tetromino> m_current_tetromino;
	Tetromino m_shaddow_tetromino;
	std::shared_ptr<Tetromino> m_next_tetromino;
	std::vector <std::vector<int>> m_figures;
	bool m_game_over = false;
	time_t randomizer_seed;
	sf::RenderWindow* m_window = nullptr;
	sf::Text m_game_over_text;
	sf::Text m_next_piece_text;
	sf::Text m_score_text;
	sf::Text m_level_text;
	sf::Text m_total_lines_text;
	sf::Text m_combo_text;
	sf::Font m_font;
	int m_combo = 0;
	int m_total_lines = 0;
	int m_score = 0;
	int m_level = 1;
};

#endif