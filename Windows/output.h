#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <iomanip>
#include <iostream>
#include <windows.h>
using namespace std;

// #include "menu.h"
#include "gameboard.h"

char
    sym_border_l[] = " ||||((({{{<<<[[[!!!",
    sym_border_r[] = " ||||)))}}}>>>]]]!!!",
    sym_horizontal[] = " ----~~~+++***===???";

class Output
{
public:

    Output(void) { cout << fixed; }
    ~Output(void) {}

    void init(GameBoard *gameboard, int *counter, bool *cheater)
    {
        _gameboard = gameboard;
        _counter = counter;
        _cheater = cheater;
    }

    void message_greeting(void)
    {
        cout << "Hi!\n";
    }

    void message_farewell(void)
    {
        cout << "Bye!\n";
    }

    void message_saved(void)
    {
        cout << "Game saved.\n";
    }

    void message_interrupt(void)
    {
        cout << "Interrupting...\n";
    }

    void message_lose(void)
    {
        cout << "You lose. =(\n";
    }

    void message_out_of_returns(void)
    {
        cout << "You are out of backsteps, my friend. =)\n";
    }

    void message_backsteps(void)
    {
        cout << "Backsteps allowed: " << _gameboard->backsteps() << '\n';
    }

    void message_counter(void)
    {
        cout << *_counter << " step\n";
    }

    void message_cheater(void)
    {
        if(*_cheater)
            cout << "Cheater!\n";
    }

    short ask_to_load(void)
    {
        short load;
        cout << "Do you want to load previously saved game? (1 - yes, 0 - no): ";
        cin >> load;
        return load;
    }

    short ask_to_size(void)
    {
        short size;
        cout << "Size = ";
        cin >> size;
        return size;
    }

    short ask_to_size_safe(void)
    {
        short size = ask_to_size();
        while(size < 2)
        {
            cout << "Size must be not below 2.\n";
            size = ask_to_size();
        }
        return size;
    }

    short ask_to_base(void)
    {
        short base;
        cout << "Base = ";
        cin >> base;
        return base;
    }

    void output(void)
    {
        short fig_size = _length_of_figure(pow(_gameboard->base(), _gameboard->max_val()));
        system("cls");
        message_cheater();
        message_counter();
        message_backsteps();
        cout << '#';
        for(short i = 0; i < _gameboard->size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
        for(short j = 0; j < _gameboard->size(); j++)
        {
            cout << '#';
            for(short i = 0; i < _gameboard->size(); i++)
            {
                cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_gameboard->gameboard()[j][i]];
                cout << ' ';
            }
            cout << "#\n#";
            for(short i = 0; i < _gameboard->size(); i++)
            {
                cout << sym_border_l[_gameboard->gameboard()[j][i]];
                cout << setw(fig_size);
                if(_gameboard->gameboard()[j][i] == 0) cout << ' ';
                else cout << static_cast<long long>(pow(_gameboard->base(), _gameboard->gameboard()[j][i]));
                cout << sym_border_r[_gameboard->gameboard()[j][i]];
            }
            cout << "#\n#";
            for(short i = 0; i < _gameboard->size(); i++)
            {   cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_gameboard->gameboard()[j][i]];
                cout << ' ';
            }
            cout << "#\n";
        }
        cout << '#';
        for(short i = 0; i < _gameboard->size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
    }

private:

    const bool *_cheater;
    const int *_counter;
    GameBoard *_gameboard;

    //returns the length of required figure
    short _length_of_figure(long long figure)
    {
        short res = 0;
        while(figure)
        {
            figure = (figure - (figure % 10)) / 10;
            res++;
        }
        return res;
    }
};

#endif
