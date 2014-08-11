#ifndef _GAME_CPP_
#define _GAME_CPP_

#include "board.h"
#include "output.h"
#include "menu.h"

int main(void)
{
    Board board;
    Output output;
    Menu menu;
    menu.init(&board, &output);
    menu.start();

    return 0;
}

#endif
