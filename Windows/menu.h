#ifndef _MENU_H_
#define _MENU_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define FILENAME "2048.sav"

#include "gameboard.h"
#include "output.h"

class Menu
{
public:

    Menu(void) { _counter = 1; }
    ~Menu(void) {}

    //main function
    void start(void)
    {
        _output->message_greeting();
        _setup();
        _output->init(this, _gameboard, &_counter);
        _output->output();
        _control();
        _output->message_farewell();
    }

    short counter(void) { return _counter; }
    bool cheater(void) { return _cheater; }

    //sets pointers to gameboard and output
    void init(GameBoard *gameboard, Output *output)
    {
        _gameboard = gameboard;
        _output = output;
    }

    //loads previously saved game
    void load_from_file(void) { _load_from_file(); }

    //saves to file
    void save_to_file(void) { _save_to_file(); }

private:

    bool _cheater;
    int _counter;
    GameBoard *_gameboard;
    Output *_output;

    void _load_from_file(void)
    {
        short base, size;
        ifstream in_file(FILENAME, ios::in | ios::binary);
        in_file.read(reinterpret_cast <char *> (&base), sizeof(short));
        in_file.read(reinterpret_cast <char *> (&size), sizeof(short));
        _gameboard->init(base, size);
        in_file.read(reinterpret_cast <char *> (&_counter), sizeof(int));
        in_file.read(reinterpret_cast <char *> (&_cheater), sizeof(bool));
        for(short j = 0; j < size; j++)
            for(short i = 0; i < size; i++)
                in_file.read(reinterpret_cast <char *> (&_gameboard->gameboard()[j][i]), sizeof(short));
        in_file.close();
    }

    void _save_to_file(void)
    {
        ofstream out_file(FILENAME, ios::out | ios::binary);
        out_file.write(reinterpret_cast <char *> (&_gameboard->base()), sizeof(short));
        out_file.write(reinterpret_cast <char *> (&_gameboard->size()), sizeof(short));
        out_file.write(reinterpret_cast <char *> (&_counter), sizeof(int));
        out_file.write(reinterpret_cast <char *> (&_cheater), sizeof(bool));
        for(short j = 0; j < _gameboard->size(); j++)
            for(short i = 0; i < _gameboard->size(); i++)
                out_file.write(reinterpret_cast <char *> (&_gameboard->gameboard()[j][i]), sizeof(short));
        out_file.close();
    }

    void _setup(void)
    {
        if(_output->ask_to_load()) { _load_from_file(); }
        else
        {
            _gameboard->init(BASE, _output->ask_to_size_safe());
            _gameboard->put_random(0);
            _gameboard->put_random(0);
        }
    }

    void _key(bool &ismoved, bool &isexit)
    {
        char dir, sym;
        sym = getch();
        dir = -1;
        switch(sym)
        {
            case 'q':
                isexit = true;
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
            case 'b':
                _gameboard->base(_output->ask_to_base());
                _output->output();
                break;
            case 'r':
                if(_gameboard->previous_position())
                {
                    _counter--;
                    _output->output();
                }
                else
                    _output->message_out_of_returns();
                break;
            case '/':
                _super_mega_cheat();
                _output->output();
                break;
            default:
                break;
        }
        if(isexit) _output->message_interrupt();
        if(dir != -1) ismoved = _gameboard->shift(dir);
    }

    bool _control(void)
    {
        bool ismoved, isexit = false;
        while(!isexit)
        {
            ismoved = false;
            while(!ismoved && !isexit) _key(ismoved, isexit);
            if(isexit) break;
            _gameboard->put_random(1);
            _counter++;
            _output->output();
            switch(_gameboard->status_checking())
            {
                case 1:
                    _output->message_lose();
                    isexit = true;
                    break;
                case 2:
                    // cout << "You win! =)\n";
                    // isexit = true;
                    break;
                default:
                    break;
            }
        }
    }

    void _super_mega_cheat(void)
    {
        bool correct = true;
        short symbols = 6;
        char sym, keyword[] = "double";
        for(short i = 0; i < symbols; i++)
        {
            sym = getch();
            if(sym != keyword[i])
            {
                correct = false;
                break;
            }
        }
        if(!correct) return;
        for(short j = 0; j < _gameboard->size(); j++)
            for(short i = 0; i < _gameboard->size(); i++)
                if(_gameboard->gameboard()[j][i] != 0)
                    _gameboard->gameboard()[j][i]++;
    }

};

#endif
