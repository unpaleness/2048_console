#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <iomanip>
#include <iostream>
using namespace std;

#include "board.h"

char
    sym_border_l[] = " ||||((({{{<<<[[[",
    sym_border_r[] = " ||||)))}}}>>>]]]",
    sym_horizontal[] = " ----~~~+++***===";

class Output
{
public:

    Output(void) { cout << fixed; }
    ~Output(void) {}

    void init(Board *board, int *counter)
    {
        _board = board;
        _counter = counter;
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
        cout << "You lose. =(";
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

    short ask_to_base(void)
    {
        short base;
        cout << "Base = ";
        cin >> base;
        return base;
    }

    void output(void)
    {
        short fig_size = _length_of_figure(pow(_board->base(), _board->max_val()));
        cout << "\033[2J\033[1;1H";
        cout << *_counter << " step\n";
        cout << '#';
        for(short i = 0; i < _board->size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
        for(short j = 0; j < _board->size(); j++)
        {
            cout << '#';
            for(short i = 0; i < _board->size(); i++)
            {
                cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_board->board()[j][i]];
                cout << ' ';
            }
            cout << "#\n#";
            for(short i = 0; i < _board->size(); i++)
            {
                cout << sym_border_l[_board->board()[j][i]];
                cout << setw(fig_size);
                if(_board->board()[j][i] == 0) cout << ' ';
                else cout << short(pow(_board->base(), _board->board()[j][i]));
                cout << sym_border_r[_board->board()[j][i]];
            }
            cout << "#\n#";
            for(short i = 0; i < _board->size(); i++)
            {   cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_board->board()[j][i]];
                cout << ' ';
            }
            cout << "#\n";
        }
        cout << '#';
        for(short i = 0; i < _board->size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
    }

private:

    const int *_counter;
    Board *_board;

    //returns the length of required figure
    int _length_of_figure(int figure)
    {
        int res = 0;
        while(figure)
        {
            figure = (figure - (figure % 10)) / 10;
            res++;
        }
        return res;
    }
};

#endif
