#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Tile.h"
#include "../include/Kbhit.h"
#include "../include/Config.h"

#include <stdio.h>
#include <chrono>
#include <unistd.h>

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
    using clock = std::chrono::high_resolution_clock;
    using ns = std::chrono::nanoseconds;

    const ns MS_PER_UPDATE = std::chrono::milliseconds(SPEED);
    auto previousTime = clock::now();
    ns lag{0};

    board.reset();
    board.draw();
    Tile new_tile = Tile();
    new_tile.build_tile();
    new_tile.move_tile(RIGHT);
    new_tile.move_tile(RIGHT);
    board.update(new_tile.bit_map);
    board.draw();

    while (true)
    {
        if (_kbhit())
        {
            char c;
            read(0, &c, 1);
            switch (c)
            {
            case 'a':
                new_tile.move_tile(LEFT);
                break;
            case 'd':
                new_tile.move_tile(RIGHT);
                break;
            default:
                break;
            }
            board.update(new_tile.bit_map);
            board.draw();
        }

        auto currentTime = clock::now();
        auto elapsed = std::chrono::duration_cast<ns>(currentTime - previousTime);
        previousTime = currentTime;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE)
        {
            new_tile.move_tile(DOWN);
            board.update(new_tile.bit_map);
            board.draw();
            lag -= MS_PER_UPDATE;
        }
    }
}

void Game::exit()
{
    printf("\x1b[?25h"); // Show the cursor
}