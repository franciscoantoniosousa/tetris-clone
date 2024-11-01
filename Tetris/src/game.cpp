#include "game.hpp"
#include <format>
#include <iostream>


Game::Game() 
{
    // seed the rand to get different tetrominos every run
    randomizer_seed = time(NULL);
    srand(static_cast<unsigned int>(randomizer_seed));

    // Setup the text
    m_font.loadFromFile("./font/8-bit.ttf");
    m_game_over_text.setFont(m_font);
    m_game_over_text.setString("GAME OVER! \n PRESS ENTER TO RESTART");
    m_game_over_text.setCharacterSize(24);
    m_game_over_text.setPosition({ 0 , RESIZED_CELL_SIZE * ROWS / 2 });

    m_next_piece_text.setFont(m_font);
    m_next_piece_text.setString("NEXT PIECE");
    m_next_piece_text.setCharacterSize(24);
    m_next_piece_text.setPosition({ (RESIZED_COLLUMNS_OFFSET + 30) , 30 });
    
    m_score_text.setFont(m_font);
    m_score_text.setString(std::format("SCORE: {0}", m_score));
    m_score_text.setCharacterSize(24);
    m_score_text.setPosition({ (RESIZED_COLLUMNS_OFFSET + 30), RESIZED_ROWS_OFFSET / 2 });
    
    m_level_text.setFont(m_font);
    m_level_text.setString(std::format("LEVEL: {0}", m_level));
    m_level_text.setCharacterSize(24);
    m_level_text.setPosition({ (RESIZED_COLLUMNS_OFFSET +30), RESIZED_ROWS_OFFSET / 2  + 30});

    m_total_lines_text.setFont(m_font);
    m_total_lines_text.setString(std::format("LINES: {0}", m_total_lines));
    m_total_lines_text.setCharacterSize(24);
    m_total_lines_text.setPosition({ (RESIZED_COLLUMNS_OFFSET + 30) , RESIZED_ROWS_OFFSET / 2 + 60 });

    m_combo_text.setFont(m_font);
    m_combo_text.setString(std::format("Combo: {0}", m_combo));
    m_combo_text.setCharacterSize(24);
    m_combo_text.setPosition({ (RESIZED_COLLUMNS_OFFSET + 30) , RESIZED_ROWS_OFFSET / 2 + 90 });

    // Set the board matrix columns to COLUMNS size
    m_board_matrix.resize(COLUMNS);
    for (int col = 0; col < m_board_matrix.size(); col++)
    {
        //  Set the number of rows per column to be ROWS size
        m_board_matrix[col].resize(ROWS);
    }
    Restart();
}

bool Game::CanTetrominoMove(std::vector<sf::Vector2f> current_tetromino)
{
    for (sf::Vector2f& square : current_tetromino)
    {
        // check if its outside the board to the left
        if (0  > square.x)
            return false;

        // check if its outside the board to the right
        if (COLUMNS == square.x)
            return false;

        // check if its overlapping another tetromino to the left
        if (0 != m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] && m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] != m_current_tetromino->getId())
            return false;

        // check if its overlapping another tetromino to the right
        if (0 != m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] && m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] != m_current_tetromino->getId())
            return false;
    }

    return true;
}

bool Game::CanTetrominoMoveDown(std::vector<sf::Vector2f> dummy_tetromino)
{
    for (sf::Vector2f& square : dummy_tetromino)
    {
        // check if any of the current shape will hit the bottom if so stop
        if (ROWS <= square.y)
        {
            return false;
        }
        // Check if the current shape is overlapping another shape
        if (m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] > 0 && m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] != m_current_tetromino->getId()) {
            return false;
        }
    }

    return true;
}

void Game::DrawBoard()
{
    // Create a dummy cell
   sf::RectangleShape dummy_cell(sf::Vector2f(RESIZED_CELL_SIZE - 2, RESIZED_CELL_SIZE - 2));
   sf::RectangleShape shaddow_cell(sf::Vector2f(RESIZED_CELL_SIZE - 2, RESIZED_CELL_SIZE - 2));

   // Draw Tetromino Shaddow
   m_shaddow_tetromino.setTetrominoPositions(m_current_tetromino->getTetrominoPositions());
   m_shaddow_tetromino.setIsBeingPlayed(true);
   while (m_shaddow_tetromino.getIsBeingPlayed())
   {
       auto dummy_tetro = m_shaddow_tetromino.MoveDown();
       if (CanTetrominoMoveDown(dummy_tetro)) {
           m_shaddow_tetromino.setTetrominoPositions(dummy_tetro);
       }
       else {
           m_shaddow_tetromino.setIsBeingPlayed(false);
       }
   }

   shaddow_cell.setFillColor(sf::Color(75, 0, 200));
   shaddow_cell.setOutlineColor(GetTetrominoColor(m_current_tetromino->getId()));
   shaddow_cell.setOutlineThickness(1);
   for (auto& square : m_shaddow_tetromino.getTetrominoPositions()) {
       int position_x = RESIZED_CELL_SIZE * static_cast<int>(square.x);
       int position_y = RESIZED_CELL_SIZE * static_cast<int>(square.y);
       shaddow_cell.setPosition(static_cast<float>(position_x), static_cast<float>(position_y));

       m_window->draw(shaddow_cell);
   }

    // Create a grid that will make up the game board
    for (int column = 0; column < COLUMNS; column++) {
        for (int row = 0; row < ROWS; row++) {
            // Set dummy_cell to a different position
            dummy_cell.setPosition(static_cast<float>(RESIZED_CELL_SIZE * column), static_cast<float>(RESIZED_CELL_SIZE * row));
            // check if the current cell block is part of any shape and set the color properly
            if (m_board_matrix[column][row] == 0) {
                dummy_cell.setFillColor(sf::Color(75, 0, 200));
                m_window->draw(dummy_cell);
            }
            else {
                dummy_cell.setFillColor(GetTetrominoColor(m_board_matrix[column][row]));
                m_window->draw(dummy_cell);
            }
        }
    }

    for (auto& square : m_next_tetromino->getTetrominoPositions())
    {
        int position_x = (RESIZED_COLLUMNS_OFFSET + 20) + (static_cast<int>(square.x) * RESIZED_CELL_SIZE);
        int position_y = 100 + (static_cast<int>(square.y) * RESIZED_CELL_SIZE);
        dummy_cell.setPosition(static_cast<float>(position_x), static_cast<float>(position_y));
        dummy_cell.setFillColor(GetTetrominoColor(m_next_tetromino->getId()));
        m_window->draw(dummy_cell);
    }

    // Scoring Area
    for (auto& square : m_next_tetromino->getTetrominoPositions())
    {
        int position_x = (RESIZED_COLLUMNS_OFFSET + 20) + (static_cast<int>(square.x) * RESIZED_CELL_SIZE);
        int position_y = 100 + (static_cast<int>(square.y) * RESIZED_CELL_SIZE);
        dummy_cell.setPosition(static_cast<float>(position_x), static_cast<float>(position_y));
        dummy_cell.setFillColor(GetTetrominoColor(m_next_tetromino->getId()));
        m_window->draw(dummy_cell);
    }


    // Text Area
    m_score_text.setString(std::format("SCORE: {0}", m_score));
    m_window->draw(m_score_text);

    m_level_text.setString(std::format("LEVEL: {0}", m_level));
    m_window->draw(m_level_text);

    m_total_lines_text.setString(std::format("LINES: {0}", m_total_lines));
    m_window->draw(m_total_lines_text);

    m_combo_text.setString(std::format("COMBO: {0}", m_combo));
    m_window->draw(m_combo_text);

    m_window->draw(m_next_piece_text);

}

void Game::DropTetromino()
{
    m_current_tetromino->setCanDrop(false);
    while (m_current_tetromino->getIsBeingPlayed()) {
        MoveTetrominoDown(m_current_tetromino);

        // hard drop
        m_score += 1;
    }
}

void Game::GameOver()
{
    m_game_over = true;
}

sf::Color Game::GetTetrominoColor(int block_id)
{
    int current_figure = block_id % 7;
    switch (current_figure)
    {
    case 0: // O Shape
        return sf::Color(sf::Color::Yellow);
        break;
    case 1: // I Shape
        return sf::Color(sf::Color::Cyan);
        break;
    case 2: // L Shape
        return sf::Color({ 255,140,0 }); // orange
        break;
    case 3: // J Shape
        return sf::Color(sf::Color::Magenta);
        break;
    case 4: // S Shape
        return sf::Color(sf::Color::Red);
        break;
    case 5: // Z Shape
        return sf::Color({ 107,142,35 }); // Green
        break;
    case 6: // T Shape
        return sf::Color({ 128,0,128 }); // Purple
        break;
    default:
        return sf::Color(75, 0, 200); // Board Color
        break;
    }
}

void Game::MoveTetrominoDown(std::shared_ptr<Tetromino>& tetromino, bool count_score)
{
    if (tetromino == nullptr) {
        tetromino = m_current_tetromino;
    }

    auto dummy_tetromino = tetromino->MoveDown();
    auto current_tetromino_positions = tetromino->getTetrominoPositions();
    if (CanTetrominoMoveDown(dummy_tetromino)) {
        tetromino->getTetrominoPositions() = dummy_tetromino;
        // remove old indices, there is a need to use 2 loops so that new position that could be old positions dont get erased
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(current_tetromino_positions[id].x)][static_cast<__int64>(current_tetromino_positions[id].y)] = 0;
        } 
        // add new indices
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(dummy_tetromino[id].x)][static_cast<__int64>(dummy_tetromino[id].y)] = tetromino->getId();
        }

        if(count_score)
        {
            // soft drop
            m_score += 1;
        }
    }
    else {
        tetromino->setIsBeingPlayed(false);
    }
}

void Game::MoveTetrominoLeft()
{
    if (m_current_tetromino->getCanMove() == false)
        return;
    auto dummy_tetromino = m_current_tetromino->MoveLeft();
    auto current_tetromino_positions = m_current_tetromino->getTetrominoPositions();
    if (CanTetrominoMove(dummy_tetromino)) {
        m_current_tetromino->getTetrominoPositions() = dummy_tetromino;
        // remove old indices, there is a need to use 2 loops so that new position that could be old positions dont get erased
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(current_tetromino_positions[id].x)][static_cast<__int64>(current_tetromino_positions[id].y)] = 0;
        }
        // add new indices
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(dummy_tetromino[id].x)][static_cast<__int64>(dummy_tetromino[id].y)] = m_current_tetromino->getId();
        }
    }
}

void Game::MoveTetrominoRight()
{
    if (m_current_tetromino->getCanMove() == false)
        return;
    auto dummy_tetromino = m_current_tetromino->MoveRight();
    auto current_tetromino_positions = m_current_tetromino->getTetrominoPositions();
    if (CanTetrominoMove(dummy_tetromino)) {
        m_current_tetromino->getTetrominoPositions() = dummy_tetromino;
        // remove old indices, there is a need to use 2 loops so that new position that could be old positions dont get erased
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(current_tetromino_positions[id].x)][static_cast<__int64>(current_tetromino_positions[id].y)] = 0;
        }
        // add new indices
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(dummy_tetromino[id].x)][static_cast<__int64>(dummy_tetromino[id].y)] = m_current_tetromino->getId();
        }
    }
}

void Game::ResetMatrix()
{
    // reset the board
    for (int column = 0; column < COLUMNS; column++) {
        for (int row = 0; row < ROWS; row++) {
            m_board_matrix[column][row] = 0;
        }
    }
}

void Game::Restart()
{
    m_game_over = false;

    // Reset the matrix
    ResetMatrix();

    // Create the first block in the game
    m_current_tetromino = std::make_shared<Tetromino>(rand());
    m_next_tetromino = std::make_shared<Tetromino>(rand());

    // Set the tetromino positions in the board
    for (sf::Vector2f& square : m_current_tetromino->getTetrominoPositions())
    {
        m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] = m_current_tetromino->getId();
    }
}

void Game::RotateTetromino()
{
    auto dummy_tetromino = m_current_tetromino->Rotate();

    auto current_tetromino_positions = m_current_tetromino->getTetrominoPositions();
    //check if it will hit other pieces
    if (CanTetrominoMove(dummy_tetromino)) {
        m_current_tetromino->getTetrominoPositions() = dummy_tetromino;
        // remove old indices, there is a need to use 2 loops so that new position that could be old positions dont get erased
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(current_tetromino_positions[id].x)][static_cast<__int64>(current_tetromino_positions[id].y)] = 0;
        }
        // add new indices
        for (int id = 0; id < dummy_tetromino.size(); id++) {
            m_board_matrix[static_cast<__int64>(dummy_tetromino[id].x)][static_cast<__int64>(dummy_tetromino[id].y)] = m_current_tetromino->getId();
        }
    }

}

void Game::ScanBoard()
{
    bool score_row = true;
    bool empty_row = true;
    int scored_lines = 0;
    for (int scanned_row = 0; scanned_row < ROWS; scanned_row++) {
        score_row = true;
        for (auto& cell : m_board_matrix) {
            if (cell[scanned_row] == 0) {
                score_row = false;
                break;
            }
        }

        // score row if all squares in a row are filled
        if (score_row)
        {
            m_total_lines++;

            // level up every 10 lines
            if (m_total_lines % 10 == 0)
            {
                m_level++;
            }

            scored_lines++;
            ScoreRow(scanned_row);
        }
    }

    if (scored_lines) {
        m_combo++;
    }
    else {
        m_combo = 0;
    }

    switch (scored_lines)
    {
    case 1:
        m_score += 100 * m_level;
        break;
    case 2:
        m_score += 300 * m_level;
        break
    ;case 3:
        m_score += 500 * m_level;
        break;
    case 4:
        m_score += 800 * m_level;
        break;
    default:
        break;
    }

    if (m_combo > 0) {
        m_score += 50 * m_combo * m_level;
    }

}

void Game::ScoreRow(int row)
{
    for (int column = 0; column < m_board_matrix.size();column++) {
        m_board_matrix[column][row] = 0;
    }

    bool empty_line;
    for (int current_row = row; row > 0; current_row--) {
        empty_line = true;
        for (auto& cell : m_board_matrix) {
            if (cell[current_row - 1] != 0) {
                empty_line = false;
                cell[current_row] = cell[current_row - 1];
                cell[current_row-1] = 0;
            }
        }

        if (empty_line) {
            break;
        }
    }
}

void Game::SpawnNewBlock()
{
    // check if the curretn block is being played 
    if ( m_current_tetromino->getIsBeingPlayed())
        return;
    ScanBoard();
    //Check if its game over
    for (sf::Vector2f& square : m_current_tetromino->getTetrominoPositions())
    {
        if (square.y == 0) {
            GameOver();
        }
    }

    // create a new one block if the last block reach the end
    m_current_tetromino = m_next_tetromino;
    m_next_tetromino = std::make_shared<Tetromino>(rand());

    // Set the tetromino positions in the board
    for (sf::Vector2f& square : m_current_tetromino->getTetrominoPositions())
    {
        m_board_matrix[static_cast<__int64>(square.x)][static_cast<__int64>(square.y)] = m_current_tetromino->getId();
    }
}

void Game::Update(bool drop_block)
{
    if(m_game_over == false)
    {
        DrawBoard();
        if (drop_block)
        {
            MoveTetrominoDown(m_current_tetromino,false);
            SpawnNewBlock();
        }
    }
    else {
        m_window->draw(m_game_over_text);
    }
}
