#pragma once
#ifndef TETRIS_GAME_BLOCK_H
#define TETRIS_GAME_BLOCK_H

#include <SFML/Graphics.hpp>
#include "global-variables.hpp"

class Tetromino {
public:
    Tetromino() { m_positions.resize(4); };
    Tetromino(int figure);

    std::vector<sf::Vector2f> Rotate();
    std::vector<sf::Vector2f> MoveRight();
    std::vector<sf::Vector2f> MoveLeft();
    std::vector<sf::Vector2f> MoveDown();

    //  Getters & Setters
    inline void setCanDrop(bool can_drop) { m_can_drop = can_drop; }
    inline bool& getCanDrop() { return m_can_drop; }
    inline sf::Color& getColor() { return m_color; }
    inline int& getId() { return m_id; }
    inline bool& getIsBeingPlayed() { return m_is_being_played; }
    inline bool& getCanMove() { return m_can_move; }
    inline std::vector<sf::Vector2f>& getTetrominoPositions() { return m_positions; }
    inline void setIsBeingPlayed(bool is_being_played) { m_is_being_played = is_being_played; }
    inline void setTetrominoPositions(std::vector<sf::Vector2f> positions) { m_positions = positions; }
private:
    sf::Color m_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    bool m_can_drop = false;
    bool m_can_move = true;
    int m_current_rotation = 0;
    int m_id = 0;
    bool m_is_being_played = false;
    bool m_last_chance_to_move = false;
    int m_move_down_count = 0;
    std::vector<sf::Vector2f> m_positions;
};

#endif