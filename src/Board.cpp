#include "../include/Board.h"

#include <cstring>
#include <stdio.h>

Board::Board() {
}

Board::~Board() {
}

void Board::reset() {

    printf("\x1b[?25l"); // Hide the cursor
    printf("\x1b[H");    // Move cursor to home position (top-left)
    printf("\x1b[2J");   // Clear the entire screen
}

void Board::draw() const {
    printf("\x1b[H");
    for (int i = 0; i < BOARD_WIDTH + 1; ++i)
        printf("##");
    printf("\n");
    for (int i = 0; i < GRID_SIZE; i += BOARD_WIDTH) {
        printf("#");
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if ((m_grid | m_current_tile)[i + j] == 0)
                printf("..");
            else
                printf("[]");
        }
        printf("#\n");
    }
    for (int i = 0; i < BOARD_WIDTH + 1; ++i)
        printf("##");
    printf("\n");
}

void Board::update(const std::bitset<GRID_SIZE> &tile_map) {
    m_current_tile = tile_map;
    draw();
}