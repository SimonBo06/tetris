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

enum Locked
{
    UNLOCKED,
    HALF_LOCKED,
    LOCKED
};

class Tile
{
public:
    Tile(TileType t, Rotation r);
    Tile();
    ~Tile();
    Rotation rot;
    TileType type;
    void build_tile();
    void rotate_tile();
    void move_tile(Direction dir, std::bitset<GRID_SIZE> &bit_map);
    std::bitset<GRID_SIZE> m_bit_map;

private:
    std::bitset<GRID_SIZE> m_left_border_mask;
    std::bitset<GRID_SIZE> m_right_border_mask;
    std::bitset<GRID_SIZE> m_bottom_border_mask;
    Locked m_lock_state = UNLOCKED;
    int m_shift = 0;
};

#endif // TILE_H