#include "../include/Tile.h"
#include "../include/Random.h"

Tile::Tile(TileType t, Rotation r)
    : type(t), rot(r)
{
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        if (i % BOARD_WIDTH == 0)
            m_left_border_mask.set(i);
        if (i % BOARD_WIDTH == (BOARD_WIDTH - 1))
            m_right_border_mask.set(i);
    }

    for (int i = 0; i < BOARD_WIDTH; ++i)
        m_bottom_border_mask.set((BOARD_HEIGHT - 1) * BOARD_WIDTH + i);

    // TODO: correct shift needs to be initialized
}

Tile::Tile()
    : Tile(static_cast<TileType>(tile_dist(gen)),
           static_cast<Rotation>(rot_dist(gen)))
{
}

Tile::~Tile()
{
}

void Tile::build_tile()
{
    m_bit_map.reset();
    switch (type)
    {
    case I:
        m_bit_map[0 + 2 * BOARD_WIDTH] = 1;
        m_bit_map[1 + 2 * BOARD_WIDTH] = 1;
        m_bit_map[2 + 2 * BOARD_WIDTH] = 1;
        m_bit_map[3 + 2 * BOARD_WIDTH] = 1;
        break;
    case O:
        m_bit_map[1] = 1;
        m_bit_map[2] = 1;
        m_bit_map[BOARD_WIDTH + 1] = 1;
        m_bit_map[BOARD_WIDTH + 2] = 1;
        break;
    case T:
        m_bit_map[1] = 1;
        m_bit_map[0 + BOARD_WIDTH] = 1;
        m_bit_map[1 + BOARD_WIDTH] = 1;
        m_bit_map[2 + BOARD_WIDTH] = 1;
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
        m_bit_map[0 + BOARD_WIDTH] = 1;
        m_bit_map[1 + BOARD_WIDTH] = 1;
        m_bit_map[2 + BOARD_WIDTH] = 1;
        break;
    case L:
        m_bit_map[0 + BOARD_WIDTH] = 1;
        m_bit_map[1 + BOARD_WIDTH] = 1;
        m_bit_map[2 + BOARD_WIDTH] = 1;
        m_bit_map[2] = 1;
        break;

    default:
        m_bit_map.set();
        break;
    }
}

void Tile::rotate_tile()
{
    if (m_lock_state != UNLOCKED)
        return;

    std::bitset<GRID_SIZE> new_bit_map;
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        std::bitset<GRID_SIZE> tmp_bit_map;
        if (m_shift > 0)
            tmp_bit_map = m_bit_map >> m_shift;
        else
            tmp_bit_map = m_bit_map << (-m_shift);
        if (!tmp_bit_map[i])
            continue;
        const int row = i / BOARD_WIDTH;
        const int col = i % BOARD_WIDTH;
        new_bit_map.set(row * 4 + (4 - 1 - col));
    }
    if (m_shift > 0)
        new_bit_map <<= m_shift;
    else
        new_bit_map >>= (-m_shift);
    // TODO: check if the new position is valid before applying the rotation
    m_bit_map = new_bit_map;
}

void Tile::move_tile(Direction dir, std::bitset<GRID_SIZE> &bit_map)
{
    if (m_lock_state != UNLOCKED)
        return;

    switch (dir)
    {
    case LEFT:
        if ((m_bit_map & (m_left_border_mask)).any())
            return;
        if (((m_bit_map << BOARD_WIDTH) & bit_map).any())
            return;
        m_bit_map >>= 1;
        --m_shift;
        break;
    case RIGHT:
        if ((m_bit_map & (m_right_border_mask)).any())
            return;
        if (((m_bit_map << BOARD_WIDTH) & bit_map).any())
            return;
        m_bit_map <<= 1;
        ++m_shift;
        break;
    case DOWN:
        if (!(m_bit_map & m_bottom_border_mask).any())
            if (!((m_bit_map << BOARD_WIDTH) & bit_map).any())
            {
                m_bit_map <<= BOARD_WIDTH;
                m_shift += BOARD_WIDTH;
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