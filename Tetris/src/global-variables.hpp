#pragma once

#ifndef TETRIS_GAME_GLOBAL_VARIABLES_H
#define TETRIS_GAME_GLOBAL_VARIABLES_H

static constexpr int CELL_SIZE = 8;
static constexpr int COLUMNS = 10;
static constexpr int ROWS = 20;
static constexpr int RESIZE_RATIO = 4;
static constexpr int RESIZED_CELL_SIZE = CELL_SIZE * RESIZE_RATIO;
static constexpr int RESIZED_COLLUMNS_OFFSET = RESIZED_CELL_SIZE * COLUMNS;
static constexpr int RESIZED_ROWS_OFFSET = RESIZED_CELL_SIZE * ROWS;

#endif // !TETRIS_GAME_GLOBAL_VARIABLES