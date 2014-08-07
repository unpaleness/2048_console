#ifndef _MENU_H_
#define _MENU_H_

#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

#define FILENAME "2048.sav"

#include "board.h"
#include "output.h"

class Output;

class Menu
{
public:

    Menu() {}
    ~Menu() {}

    short counter(void) { return _counter; }

    // void init(Board board, Output output)
    // {
    //     _board = &board;
    //     _output = &output;
    // }

private:

    int _counter;
    Board *_board;
    Output *_output;

};

#endif
