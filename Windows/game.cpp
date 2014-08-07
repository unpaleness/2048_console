#ifndef _GAME_CPP_
#define _GAME_CPP_

// #include <cmath>
// #include <conio.h>
// #include <cstdlib>
// #include <ctime>
// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <windows.h>

// using namespace std;

#include "board.h"
#include "output.h"
#include "menu.h"

void load_size(short &size)
{
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&size), sizeof(short));
    input.close();
}

void loadfile(short **a, int &counter)
{
    short size;
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&size), sizeof(short));
    input.read(reinterpret_cast <char *> (&counter), sizeof(int));
    for(short j = 0; j < size; j++)
        for(short i = 0; i < size; i++)
            input.read(reinterpret_cast <char *> (&a[j][i]), sizeof(short));
    input.close();
}

int main(void)
{
    srand(time(0));
    cout << fixed;

    Menu menu;
    Board board;
    Output output(board, menu);

    char sym;
    short dir, x, y, size;
    int counter = 0;
    bool exit = false, load, ismoved;

    // cout << "Do you want to load previously saved game? (1 - yes, 0 - no): ";
    // cin >> load;

    // if(load)
    //     load_size(size);
    // else
    // {
        cout << "Size = ";
        cin >> size;
    // }

    board.init(size);

    // short **a = new short *[size];
    // for(short i = 0; i < size; i++)
    //     a[i] = new short [size];

    // for(short j = 0; j < size; j++)
    //     for(short i = 0; i < size; i++)
    //         a[j][i] = 0;

    //initial figures
    board.put_random();
    board.put_random();

    // if(load)
    // {
    //     loadfile(board.board(), counter);
    //     counter--;
    // }

    // board.counter(counter);

    // board.print_info();
    output.output();

    /**************\
    |* main cycle *|
    \**************/
    while(!exit)
    {
        counter++;
        do
        {
            ismoved = false;
            sym = getch();
            // cin >> sym;
            dir = -1;
            switch(sym)
            {
                case 'q':
                    exit = true;
                    break;
                case 'w':
                    dir = 0;
                    break;
                case 'a':
                    dir = 1;
                    break;
                case 's':
                    dir = 2;
                    break;
                case 'd':
                    dir = 3;
                    break;
                case 'f':
                {
                    ofstream out_file(FILENAME, ios::out | ios::binary);
                    out_file.write(reinterpret_cast <char *> (board.size()), sizeof(short));
                    out_file.write(reinterpret_cast <char *> (board.counter()), sizeof(int));
                    for(short j = 0; j < size; j++)
                        for(short i = 0; i < size; i++)
                            out_file.write(reinterpret_cast <char *> (&board.board()[j][i]), sizeof(short));
                    out_file.close();
                }
                    cout << "Game saved.\n";
                    break;
                default:
                    break;
            }
            if(exit)
            {
                cout << "Interrupting...\n";
                break;
            }
            if(sym == 'f')
                continue;
            if(dir != -1)
                ismoved = board.shift(dir);
        }
        while(!ismoved);
        if(exit)
            break;
        //adding new tile
        board.put_random();
        //output
        output.output();
        //
        switch(board.status_checking())
        {
            case 1:
                cout << "You lose. =(\n";
                exit = true;
                break;
            case 2:
                // cout << "You win! =)\n";
                // exit = true;
                break;
            default:
                break;
        }
    }

    cout << "Bye!\n";

    return 0;
}

#endif
