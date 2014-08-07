#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <iomanip>
#include <iostream>
#include <windows.h>

#include "count.h"

class Output
{
    Output(Board board) { _board = &board; }
    ~Output() {}

    void output(void)
    {
        short fig_size = length_of_figure(pow(BASE, max_val(_board.board(), _board.size())));
        system("cls");
        cout << _board.counter() << " step\n";
        cout << '#';
        for(short i = 0; i < _board.size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
        for(short j = 0; j < _board.size(); j++)
        {
            cout << '#';
            for(short i = 0; i < _board.size(); i++)
            {
                cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_board.board()[j][i]];
                cout << ' ';
            }
            cout << "#\n#";
            for(short i = 0; i < _board.size(); i++)
            {
                cout << sym_border_l[_board.board()[j][i]];
                cout << setw(fig_size);
                if(_board.board()[j][i] == 0) cout << ' ';
                else cout << short(pow(BASE, _board.board()[j][i]));
                cout << sym_border_r[_board.board()[j][i]];
            }
            cout << "#\n#";
            for(short i = 0; i < _board.size(); i++)
            {   cout << ' ';
                for(short k = 0; k < fig_size; k++) cout << sym_horizontal[_board.board()[j][i]];
                cout << ' ';
            }
            cout << "#\n";
        }
        cout << '#';
        for(short i = 0; i < _board.size() * (fig_size + 2); i++)
            cout << '#';
        cout << "#\n";
    }

private:

    Board *_board;

    //returns the length of required figure
    int length_of_figure(int figure)
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

// int length_of_figure(int figure)
// {
//     int res = 0;
//     while(figure)
//     {
//         figure = (figure - (figure % 10)) / 10;
//         res++;
//     }
//     return res;
// }

// void output(short **a, short W, int counter)
// {
//     short fig_size = length_of_figure(pow(BASE, max_val(a, W)));
//     system("cls");
//     cout << counter << " step\n";
//     cout << '#';
//     for(short i = 0; i < W * (fig_size + 2); i++)
//         cout << '#';
//     cout << "#\n";
//     for(short j = 0; j < W; j++)
//     {
//         cout << '#';
//         for(short i = 0; i < W; i++)
//         {
//             cout << ' ';
//             for(short k = 0; k < fig_size; k++) cout << sym_horizontal[a[j][i]];
//             cout << ' ';
//         }
//         cout << "#\n#";
//         for(short i = 0; i < W; i++)
//         {
//             cout << sym_border_l[a[j][i]];
//             cout << setw(fig_size);
//             if(a[j][i] == 0) cout << ' ';
//             else cout << short(pow(BASE, a[j][i]));
//             cout << sym_border_r[a[j][i]];
//         }
//         cout << "#\n#";
//         for(short i = 0; i < W; i++)
//         {   cout << ' ';
//             for(short k = 0; k < fig_size; k++) cout << sym_horizontal[a[j][i]];
//             cout << ' ';
//         }
//         cout << "#\n";
//     }
//     cout << '#';
//     for(short i = 0; i < W * (fig_size + 2); i++)
//         cout << '#';
//     cout << "#\n";
// }

#endif
