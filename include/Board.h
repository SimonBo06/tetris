#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"

#include <bitset>

class Board {
  public:
    Board();
    ~Board();
    void draw() const;
    void reset();
    void update(const std::bitset<GRID_SIZE> &tile_map);
    std::bitset<GRID_SIZE> m_grid;

  private:
    // static const int BOARD_WIDTH = 10;
    // static const int BOARD_HEIGHT = 20;

    std::bitset<GRID_SIZE> m_current_tile;
};

#endif // BOARD_H
