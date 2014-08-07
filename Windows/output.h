#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <iomanip>
#include <iostream>
#include <windows.h>

#include "count.h"

int length_of_figure(int figure)
{

}

void output(short **a, short W, int counter)
{
    system("cls");
    cout << counter << " step\n";
    cout << '#';
    for(short i = 0; i < W; i++)
        cout << "#######";
    cout << "#\n";
    for(short j = 0; j < W; j++)
    {
        cout << '#';
        for(short i = 0; i < W; i++)
        {
            if(a[j][i] == 0)
                cout << setw(7) << ' ';
            if(a[j][i] > 0 & a[j][i] <= 4)
                cout << " ----- ";
            if(a[j][i] > 4 & a[j][i] <= 7)
                cout << " ~~~~~ ";
            if(a[j][i] > 7 & a[j][i] <= 10)
                cout << " +++++ ";
            if(a[j][i] > 10 & a[j][i] <= 13)
                cout << " ***** ";
            if(a[j][i] > 13 & a[j][i] <= 16)
                cout << " ===== ";
        }
        cout << "#\n#";
        for(short i = 0; i < W; i++)
        {
            if(a[j][i] == 0)
                cout << setw(7) << ' ';
            if(a[j][i] > 0 & a[j][i] <= 4)
                cout << '|' << setw(5) << short(pow(BASE, a[j][i])) << '|';
            if(a[j][i] > 4 & a[j][i] <= 7)
                cout << '(' << setw(5) << short(pow(BASE, a[j][i])) << ')';
            if(a[j][i] > 7 & a[j][i] <= 10)
                cout << '{' << setw(5) << short(pow(BASE, a[j][i])) << '}';
            if(a[j][i] > 10 & a[j][i] <= 13)
                cout << '<' << setw(5) << short(pow(BASE, a[j][i])) << '>';
            if(a[j][i] > 13 & a[j][i] <= 16)
                cout << '[' << setw(5) << short(pow(BASE, a[j][i])) << ']';
        }
        cout << "#\n#";
        for(short i = 0; i < W; i++)
        {
            if(a[j][i] == 0)
                cout << setw(7) << ' ';
            if(a[j][i] > 0 & a[j][i] <= 4)
                cout << " ----- ";
            if(a[j][i] > 4 & a[j][i] <= 7)
                cout << " ~~~~~ ";
            if(a[j][i] > 7 & a[j][i] <= 10)
                cout << " +++++ ";
            if(a[j][i] > 10 & a[j][i] <= 13)
                cout << " ***** ";
            if(a[j][i] > 13 & a[j][i] <= 16)
                cout << " ===== ";
        }
        cout << "#\n";
    }
    cout << '#';
    for(short i = 0; i < W; i++)
        cout << "#######";
    cout << "#\n";
}

#endif
