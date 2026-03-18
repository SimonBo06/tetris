#include "../include/Tile.h"
#include "../include/Random.h"

Tile::Tile(TileType t, Rotation r) : type(t), rot(r)
{
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
    {
        if (i % BOARD_WIDTH == 0)
            m_left_border_mask.set(i);
        if (i % BOARD_WIDTH == (BOARD_WIDTH - 1))
            m_right_border_mask.set(i);
    }
}

Tile::Tile() : type(static_cast<TileType>(tile_dist(gen))), rot(static_cast<Rotation>(rot_dist(gen)))
{
    for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; ++i)
    {
        if (i % BOARD_WIDTH == 0)
            m_left_border_mask.set(i);
        if (i % BOARD_WIDTH == (BOARD_WIDTH - 1))
            m_right_border_mask.set(i);
    }
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
}

void Tile::rotate_tile()
{
    // TODO: Implement rotation logic here
}

void Tile::move_tile(Direction dir)
{
    switch (dir)
    {
    case LEFT:
        if ((bit_map & m_left_border_mask).any())
            return; // Can't move left, there's a block on the left border
        bit_map >>= 1;
        break;
    case RIGHT:
        if ((bit_map & m_right_border_mask).any())
            return; // Can't move right, there's a block on the right border

        bit_map <<= 1;
        break;
    case DOWN:
        bit_map <<= BOARD_WIDTH;
        break;
    default:
        printf("Fatal Error: Invalid direction: %d\n", dir);
        exit(1);
        break;
    }
}