#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Tile.h"

#include <stdio.h>

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
    board.reset();
    board.draw();
    Tile new_tile = Tile(T, R0, 0, 0);
    new_tile.build_tile();
    new_tile.move_tile(LEFT);
    new_tile.move_tile(LEFT);
    board.update_board(new_tile.bit_map);
    board.draw();
}

void Game::exit()
{
    printf("\x1b[?25h"); // Show the cursor
}