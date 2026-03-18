#ifndef RANDOM_H
#define RANDOM_H

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

static std::uniform_int_distribution<> tile_dist(0, 6); // For TileType
static std::uniform_int_distribution<> rot_dist(0, 3);  // For Rotation

#endif // RANDOM_H