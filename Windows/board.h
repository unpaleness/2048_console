#ifndef _BOARD_H_
#define _BOARD_H_

#include <ctime>
#include <cstdlib>
#include <cmath>

#define DEFAULT_SIZE 4
#define BASE 2

class Board
{
public:

    Board(void) { srand(time(0)); }
    ~Board(void) { _memory_free(_size, _board); }

    short **board() { return _board; }
    short size(void) { return _size; }

    //initializing function
    void init(short size)
    {
        _size = size;
        _memory_alloc(size, _board);
        _nullification();
    }

    //sets initial value (1) on free space of board
    void put_random(void)
    {
        short x, y;
        do
        {
            x = rand() % _size;
            y = rand() % _size;
        }
        while(_board[y][x] != 0);
        _board[y][x] = _original_random();
    }

    //counts max value on the board
    short max_val(void)
    {
        short res = 0;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                if(_board[j][i] > res) res = _board[j][i];
        return res;
    }

    //0 - continue, 1 - lose, 2 - win
    short status_checking(void)
    {
        short counter = 0, movements = 0;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
            {
                if(_board[j][i] == 11)
                    return 2;
                if(_board[j][i] != 0)
                    counter++;
            }
        if(counter == _size * _size)
        {
            short **board_temp = new short *[_size];
            for(short i = 0; i < _size; i++)
                board_temp[i] = new short [_size];
            for(short j = 0; j < _size; j++)
                for(short i = 0; i < _size; i++)
                    board_temp[j][i] = _board[j][i];
            for(short i = 0; i < 4; i++)
                movements += shift(board_temp, i);
            for(short i = 0; i < _size; i++)
                delete [] board_temp[i];
            delete [] board_temp;
            if(movements == 0)
                return 1;
        }
        return 0;
    }

    //shift function for self board
    short shift(short dir)
    {
        return shift(_board, dir);
    }

    //dir: odd - horizontal, even - vertical
    //0 - not shifted, 1 - shifted
    short shift(short **board, short dir)
    {
        bool changed = false;
        short **board_rec;
        _memory_alloc(_size, board_rec);
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                board_rec[j][i] = board[j][i];
        //^
        if(dir == 0)
        {
            //every row..
            for(short i = 0; i < _size; i++)
            {
                short not_0 = 0;
                //erasing spaces
                for(short j = 0; j < _size; j++)
                    if(board[j][i] != 0)
                    {
                        not_0++;
                        if(j != not_0 - 1)
                        {
                            board[not_0 - 1][i] = board[j][i];
                            board[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short j = 0; j < _size - 1; j++)
                {
                    if(board[j][i] != 0)
                    {
                        if(board[j][i] == board[j + 1][i])
                        {
                            board[j][i]++;
                            board[j + 1][i] = 0;
                        }
                    }
                    else
                    {
                        for(short k = j; k < _size - 1; k++)
                            board[k][i] = board[k + 1][i];
                        board[_size - 1][i] = 0;
                        if(board[j][i] != 0)
                            j--;
                    }
                }
            }
        }
        //<-
        if(dir == 1)
        {
            //every row..
            for(short j = 0; j < _size; j++)
            {
                short not_0 = 0;
                //erasing spaces
                for(short i = 0; i < _size; i++)
                    if(board[j][i] != 0)
                    {
                        not_0++;
                        if(i != not_0 - 1)
                        {
                            board[j][not_0 - 1] = board[j][i];
                            board[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short i = 0; i < _size - 1; i++)
                {
                    if(board[j][i] != 0)
                    {
                        if(board[j][i] == board[j][i + 1])
                        {
                            board[j][i]++;
                            board[j][i + 1] = 0;
                        }
                    }
                    else
                    {
                        for(short k = i; k < _size - 1; k++)
                            board[j][k] = board[j][k + 1];
                        board[j][_size - 1] = 0;
                        if(board[j][i] != 0)
                            i--;
                    }
                }
            }
        }
        //\/
        if(dir == 2)
        {
            //every row..
            for(short i = 0; i < _size; i++)
            {
                short not_0 = _size - 1;
                //erasing spaces
                for(short j = _size - 1; j >= 0; j--)
                    if(board[j][i] != 0)
                    {
                        not_0--;
                        if(j != not_0 + 1)
                        {
                            board[not_0 + 1][i] = board[j][i];
                            board[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short j = _size - 1; j > 0; j--)
                {
                    if(board[j][i] != 0)
                    {
                        if(board[j][i] == board[j - 1][i])
                        {
                            board[j][i]++;
                            board[j - 1][i] = 0;
                        }
                    }
                    else
                    {
                        for(short k = j; k > 0; k--)
                            board[k][i] = board[k - 1][i];
                        board[0][i] = 0;
                        if(board[j][i] != 0)
                            j++;
                    }
                }
            }
        }
        //\/
        if(dir == 3)
        {
            //every row..
            for(short j = 0; j < _size; j++)
            {
                short not_0 = _size - 1;
                //erasing spaces
                for(short i = _size - 1; i >= 0; i--)
                    if(board[j][i] != 0)
                    {
                        not_0--;
                        if(i != not_0 + 1)
                        {
                            board[j][not_0 + 1] = board[j][i];
                            board[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short i = _size - 1; i > 0; i--)
                {
                    if(board[j][i] != 0)
                    {
                        if(board[j][i] == board[j][i - 1])
                        {
                            board[j][i]++;
                            board[j][i - 1] = 0;
                        }
                    }
                    else
                    {
                        for(short k = i; k > 0; k--)
                            board[j][k] = board[j][k - 1];
                        board[j][0] = 0;
                        if(board[j][i] != 0)
                            i++;
                    }
                }
            }
        }
        //checking for changes
        for(short j = 0; j < _size & !changed; j++)
            for(short i = 0; i < _size; i++)
                if(board[j][i] != board_rec[j][i])
                {
                    changed = true;
                    break;
                }

        _memory_free(_size, board_rec);

        if(changed)
            return 1;
        return 0;
    }

    // void print_info()
    // {
    //     cout << "size = " << _size << endl;
    //     for(short j = 0; j < _size; j++)
    //     {
    //         for(short i = 0; i < _size; i++)
    //             cout << _board[j][i] << ' ';
    //         cout << endl;
    //     }
    // }

private:

    short _size;
    short **_board;

    //allocates memory for some matrix
    void _memory_alloc(short size, short **&matrix)
    {
        matrix = new short *[size];
        for(short i = 0; i < size; i++)
            matrix[i] = new short [size];
    }

    //frees memory from some matrix
    void _memory_free(short size, short **&matrix)
    {
        for(short i = 0; i < size; i++)
            delete [] matrix[i];
        delete [] matrix;
    }

    //nullificates board
    void _nullification()
    {
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                _board[j][i] = 0;
    }

    //original adding rule
    short _original_random()
    {
        if(rand() % 10 > 1) return 1;
        else return 2;
    }
};

// short max_val(short **, short);
// short status_checking(short *, short);
// short shift(short **, short, short);

// //counts max value on the board
// short max_val(short **a, short W)
// {
//     short res = 0;
//     for(short j = 0; j < W; j++)
//         for(short i = 0; i < W; i++)
//             if(a[j][i] > res) res = a[j][i];
//     return res;
// }

// //0 - continue, 1 - lose, 2 - win
// short status_checking(short **a, short W)
// {
//     short counter = 0, movements = 0;
//     for(short j = 0; j < W; j++)
//         for(short i = 0; i < W; i++)
//         {
//             if(a[j][i] == 11)
//                 return 2;
//             if(a[j][i] != 0)
//                 counter++;
//         }
//     if(counter == W * W)
//     {
//         short **a_temp = new short *[W];
//         for(short i = 0; i < W; i++)
//             a_temp[i] = new short [W];
//         for(short j = 0; j < W; j++)
//             for(short i = 0; i < W; i++)
//                 a_temp[j][i] = a[j][i];
//         for(short i = 0; i < 4; i++)
//             movements += shift(a_temp, W, i);
//         for(short i = 0; i < W; i++)
//             delete [] a_temp[i];
//         delete [] a_temp;
//         if(movements == 0)
//             return 1;
//     }
//     return 0;
// }

// //dir: odd - horizontal, even - vertical
// //0 - not shifted, 1 - shifted
// short shift(short **a, short W, short dir)
// {
//     bool changed = false;
//     short **a_rec = new short *[W];
//     for(short i = 0; i < W; i++)
//         a_rec[i] = new short [W];
//     for(short j = 0; j < W; j++)
//         for(short i = 0; i < W; i++)
//             a_rec[j][i] = a[j][i];
//     //^
//     if(dir == 0)
//     {
//         //every row..
//         for(short i = 0; i < W; i++)
//         {
//             short not_0 = 0;
//             //erasing spaces
//             for(short j = 0; j < W; j++)
//                 if(a[j][i] != 0)
//                 {
//                     not_0++;
//                     if(j != not_0 - 1)
//                     {
//                         a[not_0 - 1][i] = a[j][i];
//                         a[j][i] = 0;
//                     }
//                 }
//             //calculating summas
//             for(short j = 0; j < W - 1; j++)
//             {
//                 if(a[j][i] != 0)
//                 {
//                     if(a[j][i] == a[j + 1][i])
//                     {
//                         a[j][i]++;
//                         a[j + 1][i] = 0;
//                     }
//                 }
//                 else
//                 {
//                     for(short k = j; k < W - 1; k++)
//                         a[k][i] = a[k + 1][i];
//                     a[W - 1][i] = 0;
//                     if(a[j][i] != 0)
//                         j--;
//                 }
//             }
//         }
//     }
//     //<-
//     if(dir == 1)
//     {
//         //every row..
//         for(short j = 0; j < W; j++)
//         {
//             short not_0 = 0;
//             //erasing spaces
//             for(short i = 0; i < W; i++)
//                 if(a[j][i] != 0)
//                 {
//                     not_0++;
//                     if(i != not_0 - 1)
//                     {
//                         a[j][not_0 - 1] = a[j][i];
//                         a[j][i] = 0;
//                     }
//                 }
//             //calculating summas
//             for(short i = 0; i < W - 1; i++)
//             {
//                 if(a[j][i] != 0)
//                 {
//                     if(a[j][i] == a[j][i + 1])
//                     {
//                         a[j][i]++;
//                         a[j][i + 1] = 0;
//                     }
//                 }
//                 else
//                 {
//                     for(short k = i; k < W - 1; k++)
//                         a[j][k] = a[j][k + 1];
//                     a[j][W - 1] = 0;
//                     if(a[j][i] != 0)
//                         i--;
//                 }
//             }
//         }
//     }
//     //\/
//     if(dir == 2)
//     {
//         //every row..
//         for(short i = 0; i < W; i++)
//         {
//             short not_0 = W - 1;
//             //erasing spaces
//             for(short j = W - 1; j >= 0; j--)
//                 if(a[j][i] != 0)
//                 {
//                     not_0--;
//                     if(j != not_0 + 1)
//                     {
//                         a[not_0 + 1][i] = a[j][i];
//                         a[j][i] = 0;
//                     }
//                 }
//             //calculating summas
//             for(short j = W - 1; j > 0; j--)
//             {
//                 if(a[j][i] != 0)
//                 {
//                     if(a[j][i] == a[j - 1][i])
//                     {
//                         a[j][i]++;
//                         a[j - 1][i] = 0;
//                     }
//                 }
//                 else
//                 {
//                     for(short k = j; k > 0; k--)
//                         a[k][i] = a[k - 1][i];
//                     a[0][i] = 0;
//                     if(a[j][i] != 0)
//                         j++;
//                 }
//             }
//         }
//     }
//     //\/
//     if(dir == 3)
//     {
//         //every row..
//         for(short j = 0; j < W; j++)
//         {
//             short not_0 = W - 1;
//             //erasing spaces
//             for(short i = W - 1; i >= 0; i--)
//                 if(a[j][i] != 0)
//                 {
//                     not_0--;
//                     if(i != not_0 + 1)
//                     {
//                         a[j][not_0 + 1] = a[j][i];
//                         a[j][i] = 0;
//                     }
//                 }
//             //calculating summas
//             for(short i = W - 1; i > 0; i--)
//             {
//                 if(a[j][i] != 0)
//                 {
//                     if(a[j][i] == a[j][i - 1])
//                     {
//                         a[j][i]++;
//                         a[j][i - 1] = 0;
//                     }
//                 }
//                 else
//                 {
//                     for(short k = i; k > 0; k--)
//                         a[j][k] = a[j][k - 1];
//                     a[j][0] = 0;
//                     if(a[j][i] != 0)
//                         i++;
//                 }
//             }
//         }
//     }
//     //checking for changes
//     for(short j = 0; j < W & !changed; j++)
//         for(short i = 0; i < W; i++)
//             if(a[j][i] != a_rec[j][i])
//             {
//                 changed = true;
//                 break;
//             }

//     for(short i = 0; i < W; i++)
//         delete [] a_rec[i];
//     delete [] a_rec;

//     if(changed)
//         return 1;
//     return 0;
// }

#endif
