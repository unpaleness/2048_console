#ifndef _MENU_H_
#define _MENU_H_

#include <fstream>
#include <iomanip>
#include <iostream>
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

    Menu(void) { _counter = 0; }
    ~Menu(void) {}

    //main function
    void start(void)
    {
        _output->message_greeting();
        _setup();
        _output->init(_board, _counter);
        _output->output();
        _control();
        _output->message_farewell();
    }

    //returns counter o_O
    short counter(void) { return _counter; }

    //sets pointers to board and output
    void init(Board *board, Output *output)
    {
        _board = board;
        _output = output;
    }

    //loads previously saved game
    void load_from_file(void) { _load_from_file(); }

    //saves to file
    void save_to_file(void) { _save_to_file(); }

private:

    int _counter;
    Board *_board;
    Output *_output;

    void _load_from_file(void)
    {
        short size;
        ifstream in_file(FILENAME, ios::in | ios::binary);
        in_file.read(reinterpret_cast <char *> (&size), sizeof(short));
        _board->init(size);
        in_file.read(reinterpret_cast <char *> (&_counter), sizeof(int));
        for(short j = 0; j < size; j++)
            for(short i = 0; i < size; i++)
                in_file.read(reinterpret_cast <char *> (&_board->board()[j][i]), sizeof(short));
        in_file.close();
    }

    void _save_to_file(void)
    {
        ofstream out_file(FILENAME, ios::out | ios::binary);
        out_file.write(reinterpret_cast <char *> (_board->size()), sizeof(short));
        out_file.write(reinterpret_cast <char *> (_counter), sizeof(int));
        for(short j = 0; j < _board->size(); j++)
            for(short i = 0; i < _board->size(); i++)
                out_file.write(reinterpret_cast <char *> (&_board->board()[j][i]), sizeof(short));
        out_file.close();
    }

    void _setup(void)
    {
        if(_output->ask_to_load()) { _load_from_file(); }
        else
        {
            short size;
            cout << "Size = ";
            cin >> size;
            _board->init(size);
            _board->put_random();
            _board->put_random();
        }
    }

    bool _control(void)
    {
        char dir, sym;
        bool ismoved, exit = false;
        while(!exit)
        {
            _counter++;
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
                        _save_to_file();
                        _output->message_saved();
                        break;
                    default:
                        break;
                }
                if(exit)
                {
                    _output->message_interrupt();
                    break;
                }
                if(sym == 'f')
                    continue;
                if(dir != -1)
                    ismoved = _board->shift(dir);
            }
            while(!ismoved);
            if(exit)
                break;
            //adding new tile
            _board->put_random();
            //output
            _output->output();
            //
            switch(_board->status_checking())
            {
                case 1:
                    _output->message_lose();
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
    }

};

#endif
