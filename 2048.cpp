#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define FILENAME "2048.sav"

short int power2(short int);
short int status_checking(short int **, short int);
short int shift(short int **, short int, short int);
void output(short int **, short int, int);

short int power2(short int n)
{
    short int res = 1;
    for(short int i = 0; i < n; i++)
        res *= 2;
    return res;
}

//0 - continue, 1 - lose, 2 - win
short int status_checking(short int **a, short int W)
{
    short int counter = 0, movements = 0;
    for(short int j = 0; j < W; j++)
        for(short int i = 0; i < W; i++)
        {
            if(a[j][i] == 11)
                return 2;
            if(a[j][i] != 0)
                counter++;
        }
    if(counter == W * W)
    {
        short int **a_temp = new short int *[W];
        for(short int i = 0; i < W; i++)
            a_temp[i] = new short int [W];
        for(short int j = 0; j < W; j++)
            for(short int i = 0; i < W; i++)
                a_temp[j][i] = a[j][i];
        for(short int i = 0; i < 4; i++)
            movements += shift(a_temp, W, i);
        for(short int i = 0; i < W; i++)
            delete [] a_temp[i];
        delete [] a_temp;
        if(movements == 0)
            return 1;
    }
    return 0;
}

//dir: odd - horizontal, even - vertical
//0 - not shifted, 1 - shifted
short int shift(short int **a, short int W, short int dir)
{
    bool changed = false;
    short int **a_rec = new short int *[W];
    for(short int i = 0; i < W; i++)
        a_rec[i] = new short int [W];
    for(short int j = 0; j < W; j++)
        for(short int i = 0; i < W; i++)
            a_rec[j][i] = a[j][i];
    //^
    if(dir == 0)
    {
        //every row..
        for(short int i = 0; i < W; i++)
        {
            short int not_0 = 0;
            //erasing spaces
            for(short int j = 0; j < W; j++)
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
            for(short int j = 0; j < W - 1; j++)
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
                    for(short int k = j; k < W - 1; k++)
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
        for(short int j = 0; j < W; j++)
        {
            short int not_0 = 0;
            //erasing spaces
            for(short int i = 0; i < W; i++)
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
            for(short int i = 0; i < W - 1; i++)
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
                    for(short int k = i; k < W - 1; k++)
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
        for(short int i = 0; i < W; i++)
        {
            short int not_0 = W - 1;
            //erasing spaces
            for(short int j = W - 1; j >= 0; j--)
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
            for(short int j = W - 1; j > 0; j--)
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
                    for(short int k = j; k > 0; k--)
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
        for(short int j = 0; j < W; j++)
        {
            short int not_0 = W - 1;
            //erasing spaces
            for(short int i = W - 1; i >= 0; i--)
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
            for(short int i = W - 1; i > 0; i--)
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
                    for(short int k = i; k > 0; k--)
                        a[j][k] = a[j][k - 1];
                    a[j][0] = 0;
                    if(a[j][i] != 0)
                        i++;
                }
            }
        }
    }
    //checking for changes
    for(short int j = 0; j < W & !changed; j++)
        for(short int i = 0; i < W; i++)
            if(a[j][i] != a_rec[j][i])
            {
                changed = true;
                break;
            }

    for(short int i = 0; i < W; i++)
        delete [] a_rec[i];
    delete [] a_rec;

    if(changed)
        return 1;
    return 0;
}

void output(short int **a, short int W, int counter)
{
    cout << "\033[2J\033[1;1H" << counter << " step\n";
    cout << '#';
    for(short int i = 0; i < W; i++)
        cout << "#######";
    cout << "#\n";
    for(short int j = 0; j < W; j++)
    {
        cout << '#';
        for(short int i = 0; i < W; i++)
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
        for(short int i = 0; i < W; i++)
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
        for(short int i = 0; i < W; i++)
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
    for(short int i = 0; i < W; i++)
        cout << "#######";
    cout << "#\n";
}

void loadW(short int &W)
{
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&W), sizeof(short int));
    input.close();
}

void loadfile(short int **a, int &counter)
{
    short int W;
    ifstream input(FILENAME, ios::in | ios::binary);
    input.read(reinterpret_cast <char *> (&W), sizeof(short int));
    input.read(reinterpret_cast <char *> (&counter), sizeof(int));
    for(short int j = 0; j < W; j++)
        for(short int i = 0; i < W; i++)
            input.read(reinterpret_cast <char *> (&a[j][i]), sizeof(short int));
    input.close();
}

int main(void)
{
    srand(time(0));
    cout << fixed;

    char sym;
    short int dir, x, y, W;
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

    short int **a = new short int *[W];
    for(short int i = 0; i < W; i++)
        a[i] = new short int [W];

    for(short int j = 0; j < W; j++)
        for(short int i = 0; i < W; i++)
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
                    output.write(reinterpret_cast <char *> (&W), sizeof(short int));
                    output.write(reinterpret_cast <char *> (&counter), sizeof(int));
                    for(short int j = 0; j < W; j++)
                        for(short int i = 0; i < W; i++)
                            output.write(reinterpret_cast <char *> (&a[j][i]), sizeof(short int));
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
        short int status = status_checking(a, W);
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

    for(short int i = 0; i < W; i++)
        delete [] a[i];
    delete [] a;

    cout << "Bye!\n";

    return 0;
}
