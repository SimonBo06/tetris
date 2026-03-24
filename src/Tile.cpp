#include "../include/Tile.h"
#include "../include/Random.h"

Tile::Tile(TileType t, Rotation r) : type(t), rot(r) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (i % BOARD_WIDTH == 0)
            m_left_border_mask.set(i);
        if (i % BOARD_WIDTH == (BOARD_WIDTH - 1))
            m_right_border_mask.set(i);
    }
    for (int i = 0; i < BOARD_WIDTH; ++i)
        m_bottom_border_mask.set((BOARD_HEIGHT - 1) * BOARD_WIDTH + i);
}

Tile::Tile() : type(static_cast<TileType>(tile_dist(gen))), rot(static_cast<Rotation>(rot_dist(gen))) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (i % BOARD_WIDTH == 0)
            m_left_border_mask.set(i);
        if (i % BOARD_WIDTH == (BOARD_WIDTH - 1))
            m_right_border_mask.set(i);
    }
    for (int i = 0; i < BOARD_WIDTH; ++i)
        m_bottom_border_mask.set((BOARD_HEIGHT - 1) * BOARD_WIDTH + i);
}

Tile::~Tile() {
}

void Tile::build_tile() {
    m_bit_map.reset();
    switch (type) {
    case I:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[3] = 1;
        break;
    case O:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[BOARD_WIDTH] = 1;
        m_bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case T:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case S:
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[BOARD_WIDTH] = 1;
        m_bit_map[BOARD_WIDTH + 1] = 1;
        break;
    case Z:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[BOARD_WIDTH + 1] = 1;
        m_bit_map[BOARD_WIDTH + 2] = 1;
        break;
    case J:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[BOARD_WIDTH] = 1;
        break;
    case L:
        m_bit_map[0] = 1;
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[BOARD_WIDTH + 2] = 1;
        break;

    default:
        m_bit_map.set();
        break;
    }
}

void Tile::rotate_tile() {
    // TODO rotate tile
}

void Tile::move_tile(Direction dir, std::bitset<GRID_SIZE> &bit_map) {
    if (m_lock_state != UNLOCKED)
        return;

    switch (dir) {
    case LEFT:
        if ((m_bit_map & (m_left_border_mask)).any())
            return;
        if (((m_bit_map << BOARD_WIDTH) & bit_map).any())
            return;
        m_bit_map >>= 1;
        break;
    case RIGHT:
        if ((m_bit_map & (m_right_border_mask)).any())
            return;
        if (((m_bit_map << BOARD_WIDTH) & bit_map).any())
            return;
        m_bit_map <<= 1;
        break;
    case DOWN:
        if (!(m_bit_map & m_bottom_border_mask).any())
            if (!((m_bit_map << BOARD_WIDTH) & bit_map).any()) {
                m_bit_map <<= BOARD_WIDTH;
                break;
            }
        m_lock_state = LOCKED;
        break;
    default:
        printf("Fatal Error: Invalid direction: %d\n", dir);
        exit(1);
        break;
    }
}