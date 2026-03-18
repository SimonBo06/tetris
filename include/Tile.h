#ifndef TILE_H
#define TILE_H

#include "Constants.h"

#include <bitset>

enum TileType
{
    I,
    O,
    T,
    S,
    Z,
    J,
    L
};

enum Rotation
{
    R0,
    R90,
    R180,
    R270
};

enum Direction
{
    LEFT,
    RIGHT,
    DOWN
};

class Tile
{
public:
    Tile(TileType t, Rotation r, int c, int ro);
    ~Tile();
    Rotation rot;
    TileType type;
    int col;
    int row;
    void build_tile();
    void rotate_tile();
    void move_tile(Direction dir);
    std::bitset<BOARD_WIDTH * BOARD_HEIGHT> bit_map;

private:
    std::bitset<BOARD_WIDTH * BOARD_HEIGHT> m_left_border_mask;
    std::bitset<BOARD_WIDTH * BOARD_HEIGHT> m_right_border_mask;
};

#endif // TILE_H