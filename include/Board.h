#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"

#include <bitset>

class Board
{
public:
    Board();
    ~Board();
    void draw() const;
    void reset();
    void update_board(const std::bitset<BOARD_WIDTH * BOARD_HEIGHT> &tile_map);

private:
    // static const int BOARD_WIDTH = 10;
    // static const int BOARD_HEIGHT = 20;
    std::bitset<BOARD_WIDTH * BOARD_HEIGHT> m_grid;
};

#endif // BOARD_H
