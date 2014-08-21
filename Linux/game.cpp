#ifndef _GAME_CPP_
#define _GAME_CPP_

#include "gameboard.h"
#include "output.h"
#include "menu.h"

int main(void)
{
    GameBoard gameboard;
    Output output;
    Menu menu;
    menu.init(&gameboard, &output);
    menu.start();

    return 0;
}

#endif
