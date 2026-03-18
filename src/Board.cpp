#include "../include/Board.h"

#include <cstring>
#include <stdio.h>

Board::Board()
{
    // memset(m_grid, 0, sizeof(m_grid));
}

Board::~Board()
{
}

void Board::reset()
{
    // memset(m_grid, 0, sizeof(m_grid));
    printf("\x1b[?25l"); // Hide the cursor
    printf("\x1b[H");    // Move cursor to home position (top-left)
    printf("\x1b[2J");   // Clear the entire screen
}

void Board::draw() const
{
    printf("\x1b[H");
    for (int i = 0; i < BOARD_WIDTH + 2; ++i)
        printf("==");
    printf("\n");
    for (int i = 0; i < BOARD_HEIGHT * BOARD_WIDTH; i += BOARD_WIDTH)
    {
        printf("||");
        for (int j = 0; j < BOARD_WIDTH; ++j)
        {
            if (m_grid[i + j] == 0)
                printf("..");
            else
                printf("[]");
        }
        printf("||\n");
    }
    for (int i = 0; i < BOARD_WIDTH + 2; ++i)
        printf("==");
    printf("\n");
}

void Board::update_board(const std::bitset<BOARD_WIDTH * BOARD_HEIGHT> &tile_map)
{
    m_grid |= tile_map;
}