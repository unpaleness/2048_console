#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define FILENAME "2048.sav"

short power2(short);
short status_checking(short **, short);
short shift(short **, short, short);
void output(short **, short, int);

short power2(short n)
{
    short res = 1;
    for(short i = 0; i < n; i++)
        res *= 2;
    return res;
}

//0 - continue, 1 - lose, 2 - win
short status_checking(short **a, short W)
{
    short counter = 0, movements = 0;
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
        {
            if(a[j][i] == 11)
                return 2;
            if(a[j][i] != 0)
                counter++;
        }
    if(counter == W * W)
    {
        // Читай коммент в функции main
        short **a_temp = new short *[W];
        for(short i = 0; i < W; i++)
            a_temp[i] = new short [W];
        for(short j = 0; j < W; j++)
            for(short i = 0; i < W; i++)
                a_temp[j][i] = a[j][i];
        for(short i = 0; i < 4; i++)
            movements += shift(a_temp, W, i);
        for(short i = 0; i < W; i++)
            delete [] a_temp[i];
        delete [] a_temp;
        if(movements == 0)
            return 1;
    }
    return 0;
}

//dir: odd - horizontal, even - vertical
//0 - not shifted, 1 - shifted
short shift(short **a, short W, short dir)
{
    bool changed = false;
    short **a_rec = new short *[W];
    for(short i = 0; i < W; i++)
        a_rec[i] = new short [W];
    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
            a_rec[j][i] = a[j][i];
    //^
    if(dir == 0)
    {
        //every row..
        for(short i = 0; i < W; i++)
        {
            short not_0 = 0;
            //erasing spaces
            for(short j = 0; j < W; j++)
                if(a[j][i] != 0)
                {
                    not_0++;
                    if(j != not_0 - 1)
                    {
                        a[not_0 - 1][i] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short j = 0; j < W - 1; j++)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j + 1][i])
                    {
                        a[j][i]++;
                        a[j + 1][i] = 0;
                    }
                }
                else
                {
                    for(short k = j; k < W - 1; k++)
                        a[k][i] = a[k + 1][i];
                    a[W - 1][i] = 0;
                    if(a[j][i] != 0)
                        j--;
                }
            }
        }
    }
    //<-
    if(dir == 1)
    {
        //every row..
        for(short j = 0; j < W; j++)
        {
            short not_0 = 0;
            //erasing spaces
            for(short i = 0; i < W; i++)
                if(a[j][i] != 0)
                {
                    not_0++;
                    if(i != not_0 - 1)
                    {
                        a[j][not_0 - 1] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short i = 0; i < W - 1; i++)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j][i + 1])
                    {
                        a[j][i]++;
                        a[j][i + 1] = 0;
                    }
                }
                else
                {
                    for(short k = i; k < W - 1; k++)
                        a[j][k] = a[j][k + 1];
                    a[j][W - 1] = 0;
                    if(a[j][i] != 0)
                        i--;
                }
            }
        }
    }
    //\/
    if(dir == 2)
    {
        //every row..
        for(short i = 0; i < W; i++)
        {
            short not_0 = W - 1;
            //erasing spaces
            for(short j = W - 1; j >= 0; j--)
                if(a[j][i] != 0)
                {
                    not_0--;
                    if(j != not_0 + 1)
                    {
                        a[not_0 + 1][i] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short j = W - 1; j > 0; j--)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j - 1][i])
                    {
                        a[j][i]++;
                        a[j - 1][i] = 0;
                    }
                }
                else
                {
                    for(short k = j; k > 0; k--)
                        a[k][i] = a[k - 1][i];
                    a[0][i] = 0;
                    if(a[j][i] != 0)
                        j++;
                }
            }
        }
    }
    //\/
    if(dir == 3)
    {
        //every row..
        for(short j = 0; j < W; j++)
        {
            short not_0 = W - 1;
            //erasing spaces
            for(short i = W - 1; i >= 0; i--)
                if(a[j][i] != 0)
                {
                    not_0--;
                    if(i != not_0 + 1)
                    {
                        a[j][not_0 + 1] = a[j][i];
                        a[j][i] = 0;
                    }
                }
            //calculating summas
            for(short i = W - 1; i > 0; i--)
            {
                if(a[j][i] != 0)
                {
                    if(a[j][i] == a[j][i - 1])
                    {
                        a[j][i]++;
                        a[j][i - 1] = 0;
                    }
                }
                else
                {
                    for(short k = i; k > 0; k--)
                        a[j][k] = a[j][k - 1];
                    a[j][0] = 0;
                    if(a[j][i] != 0)
                        i++;
                }
            }
        }
    }
    //checking for changes
    for(short j = 0; j < W & !changed; j++)
        for(short i = 0; i < W; i++)
            if(a[j][i] != a_rec[j][i])
            {
                changed = true;
                break;
            }

    for(short i = 0; i < W; i++)
        delete [] a_rec[i];
    delete [] a_rec;

    if(changed)
        return 1;
    return 0;
}

void output(short **a, short W, int counter)
{
    cout << "\033[2J\033[1;1H" << counter << " step\n";
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
                cout << '|' << setw(5) << power2(a[j][i]) << '|';
            if(a[j][i] > 4 & a[j][i] <= 7)
                cout << '(' << setw(5) << power2(a[j][i]) << ')';
            if(a[j][i] > 7 & a[j][i] <= 10)
                cout << '{' << setw(5) << power2(a[j][i]) << '}';
            if(a[j][i] > 10 & a[j][i] <= 13)
                cout << '<' << setw(5) << power2(a[j][i]) << '>';
            if(a[j][i] > 13 & a[j][i] <= 16)
                cout << '[' << setw(5) << power2(a[j][i]) << ']';
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

    short **a = new short *[W];
    for(short i = 0; i < W; i++)
        a[i] = new short [W];

    for(short j = 0; j < W; j++)
        for(short i = 0; i < W; i++)
            a[j][i] = 0;

    //initial figures
    a[rand() % W][rand() % W] = 1;
    do
    {
        x = rand() % W;
        y = rand() % W;
    }
    while(a[y][x] != 0);
    a[y][x] = 1;

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
            cin >> sym;
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
        a[y][x] = 1;
        //output
        output(a, W, counter);
        //
        short status = status_checking(a, W);
        switch(status)
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
