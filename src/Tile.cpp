#include "../include/Tile.h"

Tile::Tile(TileType t, Rotation r, int c, int ro) : type(t), rot(r), col(c), row(ro)
{
}

Tile::~Tile()
{
}

void Tile::build_tile()
{
    bit_map.reset();
    switch (type)
    {
    case I:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[2] = 1;
        bit_map[3] = 1;
        break;
    case O:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[BOARD_WIDTH] = 1;
        bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case T:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[2] = 1;
        bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case S:
        bit_map[1] = 1;
        bit_map[2] = 1;
        bit_map[BOARD_WIDTH] = 1;
        bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case Z:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[BOARD_WIDTH + 1] = 1;
        bit_map[BOARD_WIDTH + 2] = 1;
        break;
    case J:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[2] = 1;
        bit_map[BOARD_WIDTH] = 1;
        break;
    case L:
        bit_map[0] = 1;
        bit_map[1] = 1;
        bit_map[2] = 1;
        bit_map[BOARD_WIDTH + 2] = 1;
        break;

    default:
        bit_map.set();
        break;
    }
    rotate_tile();
    move_tile();
}

void Tile::rotate_tile()
{
    // TODO: Implement rotation logic here
}

void Tile::move_tile()
{
    // TODO: Implement movement logic here
}