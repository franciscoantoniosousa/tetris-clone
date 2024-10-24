#pragma once
#ifndef TETRIS_GAME_BLOCK_H
#define TETRIS_GAME_BLOCK_H

#include <SFML/Graphics.hpp>
#include "global-variables.hpp"

class Block {
public:
    Block() = default;
    Block(int figure);

    void UpdatePosition(sf::Vector2f& offset);
    void Rotate();
    void MoveRight(std::vector< std::vector<int>>& m_board_matrix);
    void MoveLeft(std::vector< std::vector<int>>& m_board_matrix);
    bool MoveDown(std::vector< std::vector<int>>&  m_board_matrix);

    //  Getters & Setters
    inline sf::Color& getColor() { return m_color; }
    inline int& getId() { return m_id; }
    inline bool& getIsBeingPlayed() { return m_is_being_played; }
    inline std::vector<sf::Vector2f>& getBlockPositions() { return m_positions; }
    inline void setIsBeingPlayed(bool is_being_played) { m_is_being_played = is_being_played; }
private:
    std::vector<sf::Vector2f> m_positions;
    sf::Color m_color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    bool m_is_being_played = false;
    int m_id = 0;
};

#endif