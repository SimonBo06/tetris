#ifndef GAME_H
#define GAME_H

#include "Board.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    void exit();

private:
    Board board;
};

#endif // GAME_H