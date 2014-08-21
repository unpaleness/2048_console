#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <ctime>
#include <cstdlib>
#include <cmath>

#define MEMORY 64
#define BASE 2

#include "calc.h"
#include "board.h"

//contains all states of the game
class GameBoard
{
public:

    GameBoard(void)
    {
        srand(time(0));
        _pos_begin = 0;
        _pos_current = 0;
        calc::memory_alloc(MEMORY, _gameboard);
    }
    ~GameBoard(void)
    {
        calc::memory_free(_gameboard);
    }

    short **gameboard(void) { return _gameboard[_pos_current].board(); }
    short &base(void) { return _base; }
    short &size(void) { return _size; }
    short backsteps(void)
    {
        if(_pos_current >= _pos_begin)
            return _pos_current - _pos_begin;
        else
            return _pos_current - _pos_begin + MEMORY;
    }

    void base(short value) { _base = value; }

    //initializing function
    void init(short base, short size)
    {
        _base = base;
        _size = size;
        for(short i = 0; i < MEMORY; i++)
            _gameboard[i].init(_size);
    }

    //sets initial value (1) on free space of gameboard
    void put_random(short random_type)
    {
        short x, y;
        do
        {
            x = rand() % _size;
            y = rand() % _size;
        }
        while(_gameboard[_pos_current].board()[y][x] != 0);
        if(random_type == 0) _gameboard[_pos_current].board()[y][x] = _random_simple();
        if(random_type == 1) _gameboard[_pos_current].board()[y][x] = _random_original();
    }

    //counts max value on the gameboard
    short max_val(void)
    {
        short res = 0;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
                if(_gameboard[_pos_current].board()[j][i] > res)
                    res = _gameboard[_pos_current].board()[j][i];
        return res;
    }

    //1 - successfully puts counter on previous position, 0 - no previous position
    short previous_position()
    {
        return _pos_current_decrement();
    }

    //0 - continue, 1 - lose, 2 - win
    short status_checking(void)
    {
        short counter = 0, movements = 0;
        for(short j = 0; j < _size; j++)
            for(short i = 0; i < _size; i++)
            {
                // if(_gameboard[_pos_current].board()[j][i] == 11)
                //     return 2;
                if(_gameboard[_pos_current].board()[j][i] != 0)
                    counter++;
            }
        if(counter == _size * _size)
        {
            Board tempboard, rectempboard;
            tempboard.init(_size);
            rectempboard.init(_size);
            rectempboard = _gameboard[_pos_current];
            tempboard = _gameboard[_pos_current];
            for(short i = 0; i < 4; i++)
                movements += shift(tempboard, rectempboard, i);
            if(movements == 0)
                return 1;
        }
        return 0;
    }

    //shift function for self gameboard
    short shift(short dir)
    {
        Board tempboard;
        tempboard.init(_size);
        tempboard = _gameboard[_pos_current];
        if (shift(tempboard, _gameboard[_pos_current], dir))
        {
            _pos_current_increment();
            _gameboard[_pos_current] = tempboard;
            return 1;
        }
        return 0;
    }

    //dir: odd - horizontal, even - vertical
    //0 - not shifted, 1 - shifted
    short shift(Board &gameboard, Board &recboard, short dir)
    {
        bool changed = false;
        // for(short j = 0; j < _size; j++)
        //     for(short i = 0; i < _size; i++)
        //         recboard.board()[j][i] = gameboard.board()[j][i];
        //^
        if(dir == 0)
        {
            //every row..
            for(short i = 0; i < _size; i++)
            {
                short not_0 = 0;
                //erasing spaces
                for(short j = 0; j < _size; j++)
                    if(gameboard.board()[j][i] != 0)
                    {
                        not_0++;
                        if(j != not_0 - 1)
                        {
                            gameboard.board()[not_0 - 1][i] = gameboard.board()[j][i];
                            gameboard.board()[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short j = 0; j < _size - 1; j++)
                {
                    if(gameboard.board()[j][i] != 0)
                    {
                        if(gameboard.board()[j][i] == gameboard.board()[j + 1][i])
                        {
                            gameboard.board()[j][i]++;
                            gameboard.board()[j + 1][i] = 0;
                        }
                    }
                    else
                    {
                        for(short k = j; k < _size - 1; k++)
                            gameboard.board()[k][i] = gameboard.board()[k + 1][i];
                        gameboard.board()[_size - 1][i] = 0;
                        if(gameboard.board()[j][i] != 0)
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
                    if(gameboard.board()[j][i] != 0)
                    {
                        not_0++;
                        if(i != not_0 - 1)
                        {
                            gameboard.board()[j][not_0 - 1] = gameboard.board()[j][i];
                            gameboard.board()[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short i = 0; i < _size - 1; i++)
                {
                    if(gameboard.board()[j][i] != 0)
                    {
                        if(gameboard.board()[j][i] == gameboard.board()[j][i + 1])
                        {
                            gameboard.board()[j][i]++;
                            gameboard.board()[j][i + 1] = 0;
                        }
                    }
                    else
                    {
                        for(short k = i; k < _size - 1; k++)
                            gameboard.board()[j][k] = gameboard.board()[j][k + 1];
                        gameboard.board()[j][_size - 1] = 0;
                        if(gameboard.board()[j][i] != 0)
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
                    if(gameboard.board()[j][i] != 0)
                    {
                        not_0--;
                        if(j != not_0 + 1)
                        {
                            gameboard.board()[not_0 + 1][i] = gameboard.board()[j][i];
                            gameboard.board()[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short j = _size - 1; j > 0; j--)
                {
                    if(gameboard.board()[j][i] != 0)
                    {
                        if(gameboard.board()[j][i] == gameboard.board()[j - 1][i])
                        {
                            gameboard.board()[j][i]++;
                            gameboard.board()[j - 1][i] = 0;
                        }
                    }
                    else
                    {
                        for(short k = j; k > 0; k--)
                            gameboard.board()[k][i] = gameboard.board()[k - 1][i];
                        gameboard.board()[0][i] = 0;
                        if(gameboard.board()[j][i] != 0)
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
                    if(gameboard.board()[j][i] != 0)
                    {
                        not_0--;
                        if(i != not_0 + 1)
                        {
                            gameboard.board()[j][not_0 + 1] = gameboard.board()[j][i];
                            gameboard.board()[j][i] = 0;
                        }
                    }
                //calculating summas
                for(short i = _size - 1; i > 0; i--)
                {
                    if(gameboard.board()[j][i] != 0)
                    {
                        if(gameboard.board()[j][i] == gameboard.board()[j][i - 1])
                        {
                            gameboard.board()[j][i]++;
                            gameboard.board()[j][i - 1] = 0;
                        }
                    }
                    else
                    {
                        for(short k = i; k > 0; k--)
                            gameboard.board()[j][k] = gameboard.board()[j][k - 1];
                        gameboard.board()[j][0] = 0;
                        if(gameboard.board()[j][i] != 0)
                            i++;
                    }
                }
            }
        }
        //checking for changes
        if(gameboard != recboard) changed = true;

        if(changed)
            return 1;
        return 0;
    }

private:

    short
        _pos_begin,
        _pos_current,
        _base,
        _size;
    Board *_gameboard;

    //simple adding rule
    short _random_simple()
    {
        return 1;
    }

    //original adding rule
    short _random_original()
    {
        if(rand() % 10 > 1) return 1;
        else return 2;
    }

    short _pos_next(short pos)
    {
        if(pos == MEMORY - 1)
            return 0;
        return pos + 1;
    }

    short _pos_prev(short pos)
    {
        if(pos == 0)
            return MEMORY - 1;
        return pos - 1;
    }

    //in case of looping begin position will move up
    void _pos_current_increment(void)
    {
        _pos_current = _pos_next(_pos_current);
        if(_pos_current == _pos_begin)
            _pos_begin = _pos_next(_pos_begin);
    }

    //will not do any thing in case of equality of begin and current positions
    //0 - successfully, 1 - no previous position
    short _pos_current_decrement(void)
    {
        if(_pos_begin != _pos_current)
        {
            _pos_current = _pos_prev(_pos_current);
            return 1;
        }
        return 0;
    }
};

#endif
