#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std;

#define FILENAME "2048.sav"
char
    sym_border_l[] = " ||||((({{{<<<[[[",
    sym_border_r[] = " ||||)))}}}>>>]]]",
    sym_horizontal[] = " ----~~~+++***===";

#include "output.h"
#include "count.h"

void loadW(short &W)
{
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&W), sizeof(short));
    input.close();
}

void loadfile(short **a, int &counter)
{
    short W;
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&W), sizeof(short));
    input.read(reinterpret_cast <char *> (&counter), sizeof(int));
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
            input.read(reinterpret_cast <char *> (&a[j][i]), sizeof(short));
    input.close();
}

int main(void)
{
    srand(time(0));
    cout << fixed;

    char sym;
    short dir, x, y, W;
    int counter = 0;
    bool exit = false, load, ismoved;

    cout << "Do you want to load previously saved game? (1 - yes, 0 - no): ";
    cin >> load;

    if(load)
        loadW(W);
    else
    {
        cout << "Size = ";
        cin >> W;
    }

    Board board(W, counter);
    board.nullification();

    // short **a = new short *[W];
    // for(short i = 0; i < W; i++)
    //     a[i] = new short [W];

    // for(short j = 0; j < W; j++)
    //     for(short i = 0; i < W; i++)
    //         a[j][i] = 0;

    //initial figures
    board.put_random();
    board.put_random();

    if(load)
    {
        loadfile(a, counter);
        counter--;
    }

    output(a, W, counter);

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
                    ofstream output(FILENAME, ios::out | ios::binary);
                    output.write(reinterpret_cast <char *> (&W), sizeof(short));
                    output.write(reinterpret_cast <char *> (&counter), sizeof(int));
                    for(short j = 0; j < W; j++)
                        for(short i = 0; i < W; i++)
                            output.write(reinterpret_cast <char *> (&a[j][i]), sizeof(short));
                    output.close();
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
                ismoved = shift(a, W, dir);
        }
        while(!ismoved);
        if(exit)
            break;
        //adding new tile
        do
            {
                x = rand() % W;
                y = rand() % W;
            }
        while(a[y][x] != 0);
        //some insane random figure to add }=)
        // a[y][x] = short(16 - ceil(log(rand())/log(2.0)));
        // a[y][x] = 1;
        if(rand() % 10 > 1) a[y][x] = 1;
        else a[y][x] = 2;
        //output
        output(a, W, counter);
        //
        switch(status_checking(a, W))
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

    for(short i = 0; i < W; i++)
        delete [] a[i];
    delete [] a;

    cout << "Bye!\n";

    return 0;
}
