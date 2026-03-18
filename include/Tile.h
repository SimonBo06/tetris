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
    std::bitset<BOARD_WIDTH * BOARD_HEIGHT> bit_map;

private:
    void rotate_tile();
    void move_tile();
};

#endif // TILE_H